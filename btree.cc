

/*

B-Tree(B������ƽ���������֮ͬ������:B-Tree���ڶ��������ƽ���·��������
����:
(1)����ÿ���ڵ������m���ӽڵ㣬��m>=2,��������(m��ʾһ���ڵ���m������·����m=2���Ƕ�������
(2)�����ڵ���ÿ���ڵ�Ĺؼ�������Ϊ���ڵ���ceil��m/2)-1��С�ڵ���m-1��������������
(3)����Ҷ�ӽڵ㶼��ͬһ��
(4)���һ����Ҷ�ӽڵ���n���ӽڵ㣬��ýڵ�Ĺؼ���������n-1.
(5)���нڵ�ؼ��ֶ��ǰ������������У�����ѭ��С�Ҵ�ԭ��


��ѯ�����롢ɾ����

B+����B-Tree�����档https://blog.csdn.net/jacke121/article/details/78268602
B+����B����һ�������棬�����B����˵B+������ֵ������˽ڵ�Ŀռ䣬�ò�ѯ�ٶȸ����ȶ������ٶ���ȫ�ӽ��ڶ��ַ����ҡ�Ϊʲô˵B+�����ҵ�Ч��Ҫ��B�����ߡ����ȶ��������ȿ������ߵ�����

��1��B+��B����ͬB+���ķ�Ҷ�ӽڵ㲻����ؼ��ּ�¼��ָ�룬����ʹ��B+��ÿ���ڵ����ܱ���Ĺؼ��ִ�����ӣ�

��2��B+��Ҷ�ӽڵ㱣���˸��ڵ�����йؼ��ֺ͹ؼ��ּ�¼��ָ�룬ÿ��Ҷ�ӽڵ�Ĺؼ��ִ�С�������ӣ�

��3��B+���ĸ��ڵ�ؼ������������ӽڵ�������;

��4��B+�ķ�Ҷ�ӽڵ�ֻ�������������������ʵ�ʵĹؼ��ּ�¼��ָ�룬�������ݵ�ַ����Ҫ��Ҷ�ӽڵ���ܻ�ȡ��������ÿ�����ݲ�ѯ�Ĵ�����һ����

�ص㣺
��B���Ļ�����ÿ���ڵ�洢�Ĺؼ��������࣬���Ĳ㼶�������Բ�ѯ���ݸ��죬����ָ�ؼ���ָ�붼����Ҷ�ӽڵ㣬����ÿ�β��ҵĴ�������ͬ���Բ�ѯ�ٶȸ��ȶ�;


B*��
B*����B+���ı��֣������B+�����ǵĲ�֮ͬ�����£�

��1�������ǹؼ��ָ����������⣬B+����ʼ���Ĺؼ��ֳ�ʼ��������cei(m/2)��b*���ĳ�ʼ������Ϊ��cei(2/3*m)��

��2��B+���ڵ���ʱ�ͻ���ѣ���B*���ڵ���ʱ�����ֵܽڵ��Ƿ�������Ϊÿ���ڵ㶼��ָ���ֵܵ�ָ�룩������ֵܽڵ�δ�������ֵܽڵ�ת�ƹؼ��֣�����ֵܽڵ���������ӵ�ǰ�ڵ���ֵܽڵ���ó�1/3�����ݴ���һ���µĽڵ������

�ص㣺

��B+���Ļ����������ʼ�����������ʹ�ýڵ�ռ�ʹ���ʸ��ߣ����ִ����ֵܽڵ��ָ�룬�������ֵܽڵ�ת�ƹؼ��ֵ�����ʹ��B*����ֽ������ø��٣�
��������������������������������
��Ȩ����������ΪCSDN������ShellCollector����ԭ�����£���ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/jacke121/article/details/78268602


�ܽ᣺��ƽ���������B����B+����B*�������������ǵĹ᳹��˼������ͬ�ģ����ǲ��ö��ַ�������ƽ������������������ݵ��ٶȣ�

��ͬ��������һ��һ�����ݱ�Ĺ�����ͨ��IO�Ӵ��̶�ȡ���ݵ�ԭ������һ�������ݱ䣬ÿһ���ݱ䶼��Ϊ���ýڵ�Ŀռ�������������������Ӷ�ʹ���Ĳ㼶���ٴﵽ���ٲ������ݵ�Ŀ�ģ�
��������������������������������
��Ȩ����������ΪCSDN������ShellCollector����ԭ�����£���ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/jacke121/article/details/78268602
*/