#ifndef CONFIG_H_
#define CONFIG_H_

#define FILENAME "cfg.txt"
#define FLEN 1024 * 8

class Config
{
public:
	//去除字符串首位空格
	void trim(char *strIn, char *strOut);

	//根据key得到value
	void getValue(char * keyAndValue, const char * key, char * value);
	
	//写入配置文件
	int writeCFG(const char *filename, const char *key, const char *value);

	//读取配置文件
	void readCFG(const char *filename, const char *key, char **value);

	void menu();

	int tWrite();

	void tRead();
};


#endif