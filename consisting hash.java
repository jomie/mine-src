package webspider.consistenthash;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Collection;
import java.util.HashSet;
import java.util.SortedMap;
import java.util.TreeMap;

/**
 * hash����������key����hash
 * 
 * @author typ
 * 
 */
public class HashFunction {
	/**
	 * ��MD5ѹ���㷨������hashmap��keyֵ
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
			// MD5�Ľ����128λ�ĳ���������ŵ�tmp��
			byte tmp[] = md.digest();
			s = toHex(tmp);

		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		return s;
	}

	/**
	 * �������Ƶĳ�����ת��Ϊ16���Ƶ����֣����ַ�����ʾ
	 * 
	 * @param bytes
	 * @return
	 */
	public String toHex(byte[] bytes) {
		// hexDigits���ô��ǣ��������ֽ�ת��Ϊʮ�����Ƶ�����
		char hexDigits[] = "0123456789abcdef".toCharArray();
		// MD5�Ľ����128λ�ĳ����������ֽڱ�ʾ����16���ֽڣ���ʮ�����Ʊ�ʾ�Ļ���ʹ�������ַ������Ա�ʾ��ʮ��������Ҫ32���ַ�
		char str[] = new char[16 * 2];
		int k = 0;
		for (int i = 0; i < 16; i++) {
			byte b = bytes[i];
			// �߼�����4λ����0xf��00001111�����룬Ϊ����λ��ֵ��Ȼ����hexDigits�������ҵ���Ӧ��16����ֵ
			str[k++] = hexDigits[b >>> 4 & 0xf];
			// ��0xf��00001111�����룬Ϊ����λ��ֵ��Ȼ����hexDigits�������ҵ���Ӧ��16����ֵ
			str[k++] = hexDigits[b & 0xf];

		}
		String s = new String(str);
		return s;
	}
}

/**
 * ����һ����hash������õ�����Ҫ��ŵķ�����
 * 
 * @author typ
 * 
 * @param <T>
 */
public class ConsistentHash<T> {
	// ��ϣ�����࣬��������Լ����壬������MD5ѹ����
	private final HashFunction hashFunction;
	// ����ڵ����
	private final int numberOfReplicas;
	// ���������map
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
	 * map����ӷ������ڵ�
	 * 
	 * @param node
	 */
	public void add(T node) {
		String key;
		// ����ڵ����ڵ�hash������Ŷ�Ӧ��ʵ�ʵĽڵ������
		for (int i = 0; i < numberOfReplicas; i++) {
			key = node.toString() + i;
			circle.put(hashFunction.hash(key), node);
		}
	}

	/**
	 * map���Ƴ��������ڵ�
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
	 * ���ݶ����keyֵ��ӳ�䵽hash���У��õ������hashֵ����ķ����������Ƕ������ŵķ�����
	 * 
	 * @param key
	 * @return
	 */
	public T get(Object key) {
		if (circle.isEmpty()) {
			return null;
		}
		// �õ������hashֵ�����ݸ�hashֵ��hashֵ��ӽ��ķ�����
		String hash = hashFunction.hash((String) key);
		// ����Ϊ���Ĳ��֣�Ѱ��������hash�����hashָ��ķ�����
		// ���hash��circle��û�и�hashֵ
		if (!circle.containsKey(hash)) {
			// tailMapΪ���ڸ�hashֵ��circle�Ĳ���
			SortedMap<String, T> tailMap = circle.tailMap(hash);
			// tailMap.isEmpty()��ʾû�д��ڸ�hash��hashֵ
			// ���û�д��ڸ�hash��hashֵ����ô��circleͷ��ʼ�ҵ�һ��������д��ڸ�hashֵ��hash����ô���ǵ�һ�����ڸ�hashֵ��hashΪ������
			// ���߼��Ϲ���һ����������ﵽ������ͷ��ʼ
			hash = tailMap.isEmpty() ? circle.firstKey() : tailMap.firstKey();
		}
		return circle.get(hash);
	}

	/**
	 * ����
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		// ���弸�������������ƣ���ŵ�������
		Collection<String> nodes = new HashSet<String>();
		nodes.add("192.0.0.1");
		nodes.add("192.0.0.2");
		nodes.add("192.0.0.3");
		nodes.add("192.0.0.4");
		nodes.add("192.0.0.5");
		nodes.add("192.0.0.6");
		// MD5ѹ���㷨ʵ�ֵ�hash����
		HashFunction hashFunction = new HashFunction();
		ConsistentHash<String> cHash = new ConsistentHash<String>(hashFunction,
				4, nodes);
		// �����keyֵΪ"google_baidu"
		String key[] = { "google", "163", "baidu", "sina" };
		// ����һ���Թ�ϣ���õ��ö���Ӧ�ô�ŵķ�����
		String server[] = new String[key.length];
		for (int i = 0; i < key.length; i++) {
			server[i] = cHash.get(key[i]);
			System.out.println("���� " + key[i] + " ����ڷ������� " + server[i]);
		}
	}
}

