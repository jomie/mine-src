#ifndef VECTOR_H
#define VECTOR_H
#include <cstdio>



class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };





template <typename Object>
        class Vector
{
public:
    explicit Vector( int initSize = 0 )
        : theSize( initSize ), theCapacity( initSize + SPARE_CAPACITY ), currentIndex(0)
    {
        objects = new Object[ theCapacity ];
    }
    Vector( const Vector & rhs ) : objects( NULL )
    {
        operator=( rhs );
    }
    ~Vector( )
    {
        delete [ ] objects;
    }

    bool empty( ) const
    {
        return size( ) == 0;
    }
    int size( ) const
    {
        return theSize;
    }
    int capacity( ) const
    {
        return theCapacity;
    }

    //操作符[]重载
    Object & operator[]( int index )
    {
#ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException( );
#endif
        return objects[ index ];
    }
    //const操作符[]重载
    const Object & operator[]( int index ) const
    {
#ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException( );
#endif
        return objects[ index ];
    }
    //操作符=重载，实现对象复制
    const Vector & operator= ( const Vector & rhs )
                             {
        if( this != &rhs ) {
            delete [ ] objects;
            theSize = rhs.size( );
            theCapacity = rhs.theCapacity;

            objects = new Object[ capacity( ) ];
            for( int k = 0; k < size( ); k++ )
                objects[ k ] = rhs.objects[ k ];
        }
        return *this;
    }
    //重新设置vector尺寸（两倍）
    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }
    //设置vector尺寸（修改大小，并拷贝所有元素到新的数组，并销毁原来的数组）
    void reserve( int newCapacity )
    {
        Object *oldArray = objects;
        //1.重设size,capacity
        int numToCopy = newCapacity < theSize ? newCapacity : theSize;
        //capacity是在size的基础上加一个常数
        newCapacity += SPARE_CAPACITY;
        //2.建立新的数组，并拷贝元素到新数组
        objects = new Object[ newCapacity ];
        for( int k = 0; k < numToCopy; k++ )
            objects[ k ] = oldArray[ k ];

        theSize = numToCopy;
        theCapacity = newCapacity;
        //删除原来的数组
        delete [ ] oldArray;
    }

    // Stacky stuff
    //放置元素，一旦容量达到最大就重置大小
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }
    //删除最后元素
    void pop_back( )
    {
        if( empty( ) )
            throw UnderflowException( );
        theSize--;
    }
    //最后元素
    const Object & back ( ) const
    {
        if( empty( ) )
            throw UnderflowException( );
        return objects[ theSize - 1 ];
    }



    //为了遍历vector中的元素，实现一个iterator迭代器(迭代器其实就是指向数组的指针,并对指针操作进行了封装)
    // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin( )
    {
        currentIndex = 0;
        return &objects[ currentIndex ];
    }
    const_iterator begin( ) const
    {
        currentIndex = 0;
        return &objects[ currentIndex ];
    }
    iterator end( )
    {
        return &objects[size( )];
    }
    const_iterator end( ) const
    {
        return &objects[size( )];
    }
    iterator next()
    {
        currentIndex++;
        if( currentIndex < 0 || currentIndex > size( ) )
            throw ArrayIndexOutOfBoundsException( );
        return &objects[currentIndex];
    }
    //插入操作
    void insert(int position,  const Object & x )
    {
        //从这里我们也可以看出，插入操作会导致迭代器失效的原因所在（从新分配了空间，原迭代器变成了悬垂指针）
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        if(position > theSize || position < 0) {
            throw ArrayIndexOutOfBoundsException( );
        } else {
            for(int i=theSize-1; i>=position; i--) {
                objects[i+1] = objects[i];
            }
            objects[ position ] = x;
            theSize++;
        }
    }
    //插入（利用迭代器）
    iterator insert(iterator position, const Object& x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        if(position<begin() || position>end())
            throw ArrayIndexOutOfBoundsException( );
        iterator ite = end();
        while(ite != position) {
            *ite = *(ite-1);
            ite--;
        }
        *position = x;
        theSize++;
        return begin();
    }

    //擦除从指定位置起数据
    iterator erase(iterator position)
    {
        if(position<begin() || position>end())
            throw ArrayIndexOutOfBoundsException( );
        while(position != end()) {
            theSize--;
        }
        return begin();
    }
    //擦除从指定范围内的数据
    iterator erase(iterator first, iterator last)
    {
        if((first < begin() || first>end()) || (last < begin() || last>end()) || first>last)
            throw ArrayIndexOutOfBoundsException( );
        if(last == end())	erase(first);

        //1.先将指定范围内的数据覆盖
        int i=1;
        while(first != last+1) {
            *first = *(last+i);
            first++;
            theSize--;
            i++;
        }
        //2.将覆盖所用数据剩余部分前移（如1,2,3,4,5,6要删除2,3先用4,5覆盖2,3-->1,4,5,4,5,6-->然后6前移到4的位置-->1,4,5,6）
        i--;
        while(last <= end()) {
            last++;
            *last = *(last+i);
        }
        return begin();
    }

    bool isEnd()
    {
        if(currentIndex < 0 || currentIndex >= size( ))
            return true;
        return false;
    }
    //操作符++重载(前增量，++a)，注还有后增量的重载差不多，只是Object & operator++(int a)有参数
    Object & operator++()
    {
        currentIndex++;
        if( currentIndex < 0 || currentIndex > size( ) )
            throw ArrayIndexOutOfBoundsException( );
        return objects[ currentIndex ];
    }

    //操作符--重载
    Object & operator--()
    {
        currentIndex--;
        if( currentIndex < 0 || currentIndex > size( ) )
            throw ArrayIndexOutOfBoundsException( );
        return objects[ currentIndex ];
    }

    enum { SPARE_CAPACITY = 16 };

private:
    int theSize;
    int theCapacity;
    int currentIndex;//仅用于iterator
    Object * objects;
};

#endif
