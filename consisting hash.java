package webspider.consistenthash;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Collection;
import java.util.HashSet;
import java.util.SortedMap;
import java.util.TreeMap;

/**
 * hash函数，根据key生成hash
 * 
 * @author typ
 * 
 */
public class HashFunction {
	/**
	 * 用MD5压缩算法，生成hashmap的key值
	 * 
	 * @param source
	 * @return
	 * @throws NoSuchAlgorithmException
	 */
	public String hash(String key) {
		String s = null;

		MessageDigest md;
		try {
			md = MessageDigest.getInstance("MD5");
			md.update(key.getBytes());
			// MD5的结果：128位的长整数，存放到tmp中
			byte tmp[] = md.digest();
			s = toHex(tmp);

		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		return s;
	}

	/**
	 * 将二进制的长整数转换为16进制的数字，以字符串表示
	 * 
	 * @param bytes
	 * @return
	 */
	public String toHex(byte[] bytes) {
		// hexDigits的用处是：将任意字节转换为十六进制的数字
		char hexDigits[] = "0123456789abcdef".toCharArray();
		// MD5的结果：128位的长整数，用字节表示就是16个字节，用十六进制表示的话，使用两个字符，所以表示成十六进制需要32个字符
		char str[] = new char[16 * 2];
		int k = 0;
		for (int i = 0; i < 16; i++) {
			byte b = bytes[i];
			// 逻辑右移4位，与0xf（00001111）相与，为高四位的值，然后再hexDigits数组中找到对应的16进制值
			str[k++] = hexDigits[b >>> 4 & 0xf];
			// 与0xf（00001111）相与，为低四位的值，然后再hexDigits数组中找到对应的16进制值
			str[k++] = hexDigits[b & 0xf];

		}
		String s = new String(str);
		return s;
	}
}

/**
 * 利用一致性hash，计算得到对象要存放的服务器
 * 
 * @author typ
 * 
 * @param <T>
 */
public class ConsistentHash<T> {
	// 哈希函数类，这个类由自己定义，可以用MD5压缩法
	private final HashFunction hashFunction;
	// 虚拟节点个数
	private final int numberOfReplicas;
	// 建立有序的map
	private final SortedMap<String, T> circle = new TreeMap<String, T>();

	public ConsistentHash(HashFunction hashFunction, int numberOfReplicas,
			Collection<T> nodes) {
		this.hashFunction = hashFunction;
		this.numberOfReplicas = numberOfReplicas;
		for (T node : nodes) {
			add(node);
		}
	}

	/**
	 * map中添加服务器节点
	 * 
	 * @param node
	 */
	public void add(T node) {
		String key;
		// 虚拟节点所在的hash处，存放对应的实际的节点服务器
		for (int i = 0; i < numberOfReplicas; i++) {
			key = node.toString() + i;
			circle.put(hashFunction.hash(key), node);
		}
	}

	/**
	 * map中移除服务器节点
	 * 
	 * @param node
	 */
	public void remove(T node) {
		String key;
		for (int i = 0; i < numberOfReplicas; i++) {
			key = node.toString() + i;
			circle.remove(hashFunction.hash(key));
		}
	}

	/**
	 * 根据对象的key值，映射到hash表中，得到与对象hash值最近的服务器，就是对象待存放的服务器
	 * 
	 * @param key
	 * @return
	 */
	public T get(Object key) {
		if (circle.isEmpty()) {
			return null;
		}
		// 得到对象的hash值，根据该hash值找hash值最接近的服务器
		String hash = hashFunction.hash((String) key);
		// 以下为核心部分，寻找与上面hash最近的hash指向的服务器
		// 如果hash表circle中没有该hash值
		if (!circle.containsKey(hash)) {
			// tailMap为大于该hash值的circle的部分
			SortedMap<String, T> tailMap = circle.tailMap(hash);
			// tailMap.isEmpty()表示没有大于该hash的hash值
			// 如果没有大于该hash的hash值，那么从circle头开始找第一个；如果有大于该hash值得hash，那么就是第一个大于该hash值的hash为服务器
			// 既逻辑上构成一个环，如果达到最后，则从头开始
			hash = tailMap.isEmpty() ? circle.firstKey() : tailMap.firstKey();
		}
		return circle.get(hash);
	}

	/**
	 * 测试
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		// 定义几个服务器的名称，存放到集合中
		Collection<String> nodes = new HashSet<String>();
		nodes.add("192.0.0.1");
		nodes.add("192.0.0.2");
		nodes.add("192.0.0.3");
		nodes.add("192.0.0.4");
		nodes.add("192.0.0.5");
		nodes.add("192.0.0.6");
		// MD5压缩算法实现的hash函数
		HashFunction hashFunction = new HashFunction();
		ConsistentHash<String> cHash = new ConsistentHash<String>(hashFunction,
				4, nodes);
		// 对象的key值为"google_baidu"
		String key[] = { "google", "163", "baidu", "sina" };
		// 利用一致性哈希，得到该对象应该存放的服务器
		String server[] = new String[key.length];
		for (int i = 0; i < key.length; i++) {
			server[i] = cHash.get(key[i]);
			System.out.println("对象 " + key[i] + " 存放于服务器： " + server[i]);
		}
	}
}

