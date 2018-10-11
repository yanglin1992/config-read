#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Config::trim(char *strIn, char *strOut){

	char *start, *end, *temp;//����ȥ���ո���ַ�����ͷβָ��ͱ���ָ��

	temp = strIn;

	while (*temp == ' '){
		++temp;

	}

	start = temp; //���ͷָ��

	temp = strIn + strlen(strIn) - 1; //�õ�ԭ�ַ������һ���ַ���ָ��(����'\0')

	while (*temp == ' '){
		--temp;

	}

	end = temp; //���βָ��


	for (strIn = start; strIn <= end;){
		*strOut++ = *strIn++;

	}

	*strOut = '\0';

}

void Config::getValue(char * keyAndValue, const char * key, char * value)
{
	char *p = keyAndValue;

	p = strstr(keyAndValue, key);
	if (p == NULL){
		//printf("û��key\n");
		return;

	}

	p += strlen(key);
	trim(p, value);

	p = strstr(value, "=");
	if (p == NULL){
		printf("û��=\n");
		return;
	}
	p += strlen("=");
	trim(p, value);

	p = strstr(value, "=");
	if (p != NULL){
		printf("�����=\n");
		return;

	}
	p = value;
	trim(p, value);
}
int Config::writeCFG(const char *filename/*in*/, const char *key/*in*/, const char *value/*in*/){

	FILE *pf = NULL;
	char ftemp[FLEN] = { 0 }, fline[1024] = { 0 }, *fp;    //�ļ���������
	long fsize = 0;
	int reg = 0;
	int exit = 0;
	int i = 0;

	pf = fopen(filename, "r+");
	if (pf == NULL){
		pf = fopen(filename, "w+");

	}
	//����ļ���С
	fseek(pf, 0, SEEK_END); // ���ļ�ָ��ָ��ĩβ
	fsize = ftell(pf);
	if (fsize > FLEN){
		printf("�ļ����ܳ���8k\n");
		reg = -1;
		goto end;

	}
	fseek(pf, 0, SEEK_SET); //���ļ�ָ��ָ��ͷ

	//һ��һ�еĶ����������key���޸�value�浽����������
	while (!feof(pf)){
		fgets(fline, 1024, pf);
		if (strstr(fline, key) != NULL && exit == 1)
			strcpy(fline, "");
		if (strstr(fline, key) != NULL && exit == 0){ //�ж�key�Ƿ����
			exit = 1;
			sprintf(fline, "%s=%s\r\n", key, value);
		}

		strcat(ftemp, fline);
	}
	if (exit != 1){//������������key valueд�뵽���һ��
		sprintf(fline, "%s=%s\r\n", key, value);
		strcat(ftemp, fline);
	}
	if (pf != NULL){
		fclose(pf);
		pf = fopen(filename, "w+");
		fp = (char *)malloc(sizeof(char) * strlen(ftemp) + 1);
		strcpy(fp, ftemp);
		fp[strlen(fp) - 1] = EOF;
		fputs(fp, pf);
		if (fp != NULL){
			free(fp);
			fp = NULL;
		}
		fclose(pf);
	}
end:
	if (pf != NULL)
		fclose(pf);
	//���´���һ����filename�������ļ�
	return reg;
}

void Config::readCFG(const char *filename/*in*/, const char *key/*in*/, char **value/*out*/)
{
	FILE *pf = NULL;
	char line[1024] = { 0 }, vtemp[1024] = { 0 };

	pf = fopen(filename, "r"); //��ֻ����ʽ��

	while (!feof(pf)){
		fgets(line, 1024, pf);
		getValue(line, key, vtemp);
		if (strlen(vtemp) != 0)
			break;

	}
	if (strlen(vtemp) != 0){
		*value = (char *)malloc(sizeof(char) * strlen(vtemp) + 1);
		strcpy(*value, vtemp);

	}
	else
		* value = NULL;
	if (pf != NULL)
		fclose(pf);
}

void Config::menu(){
	printf("===========================\n");
	printf("1 д�������ļ�\n");
	printf("2 ��ȡ�����ļ�\n");
	printf("0 �˳�����");
	printf("===========================\n");
}

int Config::tWrite(){

	char key[1024] = { 0 }, value[1024] = { 0 };

	printf("������key:");
	scanf("%s", key);
	printf("������value:");
	scanf("%s", value);
	printf("\n��������ǣ�%s = %s\n", key, value);

	return writeCFG(FILENAME/*in*/, key/*in*/, value/*in*/);
}

void Config::tRead()
{
	char key[1024] = { 0 }, *value;

	printf("������key:");
	scanf("%s", key);

	readCFG(FILENAME/*in*/, key/*in*/, &value/*out*/);
	if (value == NULL){
		printf("û��key\n");
		return;

	}
	printf("\nvalue = %s\n", value);

	if (value != NULL){
		free(value);
		value = NULL;
	}
}