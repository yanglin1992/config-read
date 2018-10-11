#ifndef CONFIG_H_
#define CONFIG_H_

#define FILENAME "cfg.txt"
#define FLEN 1024 * 8

class Config
{
public:
	//ȥ���ַ�����λ�ո�
	void trim(char *strIn, char *strOut);

	//����key�õ�value
	void getValue(char * keyAndValue, const char * key, char * value);
	
	//д�������ļ�
	int writeCFG(const char *filename, const char *key, const char *value);

	//��ȡ�����ļ�
	void readCFG(const char *filename, const char *key, char **value);

	void menu();

	int tWrite();

	void tRead();
};


#endif