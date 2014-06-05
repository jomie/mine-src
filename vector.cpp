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

    //������[]����
    Object & operator[]( int index )
    {
#ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException( );
#endif
        return objects[ index ];
    }
    //const������[]����
    const Object & operator[]( int index ) const
    {
#ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException( );
#endif
        return objects[ index ];
    }
    //������=���أ�ʵ�ֶ�����
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
    //��������vector�ߴ磨������
    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }
    //����vector�ߴ磨�޸Ĵ�С������������Ԫ�ص��µ����飬������ԭ�������飩
    void reserve( int newCapacity )
    {
        Object *oldArray = objects;
        //1.����size,capacity
        int numToCopy = newCapacity < theSize ? newCapacity : theSize;
        //capacity����size�Ļ����ϼ�һ������
        newCapacity += SPARE_CAPACITY;
        //2.�����µ����飬������Ԫ�ص�������
        objects = new Object[ newCapacity ];
        for( int k = 0; k < numToCopy; k++ )
            objects[ k ] = oldArray[ k ];

        theSize = numToCopy;
        theCapacity = newCapacity;
        //ɾ��ԭ��������
        delete [ ] oldArray;
    }

    // Stacky stuff
    //����Ԫ�أ�һ�������ﵽ�������ô�С
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }
    //ɾ�����Ԫ��
    void pop_back( )
    {
        if( empty( ) )
            throw UnderflowException( );
        theSize--;
    }
    //���Ԫ��
    const Object & back ( ) const
    {
        if( empty( ) )
            throw UnderflowException( );
        return objects[ theSize - 1 ];
    }



    //Ϊ�˱���vector�е�Ԫ�أ�ʵ��һ��iterator������(��������ʵ����ָ�������ָ��,����ָ����������˷�װ)
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
    //�������
    void insert(int position,  const Object & x )
    {
        //����������Ҳ���Կ�������������ᵼ�µ�����ʧЧ��ԭ�����ڣ����·����˿ռ䣬ԭ���������������ָ�룩
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
    //���루���õ�������
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

    //������ָ��λ��������
    iterator erase(iterator position)
    {
        if(position<begin() || position>end())
            throw ArrayIndexOutOfBoundsException( );
        while(position != end()) {
            theSize--;
        }
        return begin();
    }
    //������ָ����Χ�ڵ�����
    iterator erase(iterator first, iterator last)
    {
        if((first < begin() || first>end()) || (last < begin() || last>end()) || first>last)
            throw ArrayIndexOutOfBoundsException( );
        if(last == end())	erase(first);

        //1.�Ƚ�ָ����Χ�ڵ����ݸ���
        int i=1;
        while(first != last+1) {
            *first = *(last+i);
            first++;
            theSize--;
            i++;
        }
        //2.��������������ʣ�ಿ��ǰ�ƣ���1,2,3,4,5,6Ҫɾ��2,3����4,5����2,3-->1,4,5,4,5,6-->Ȼ��6ǰ�Ƶ�4��λ��-->1,4,5,6��
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
    //������++����(ǰ������++a)��ע���к����������ز�ֻ࣬��Object & operator++(int a)�в���
    Object & operator++()
    {
        currentIndex++;
        if( currentIndex < 0 || currentIndex > size( ) )
            throw ArrayIndexOutOfBoundsException( );
        return objects[ currentIndex ];
    }

    //������--����
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
    int currentIndex;//������iterator
    Object * objects;
};

#endif
