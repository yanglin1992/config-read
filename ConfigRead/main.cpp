#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

int main()
{
	Config cfg;

	int choose;
	while (1){
		choose = 0;
		cfg.menu();
		printf("«Î ‰»Î—°‘Ò:");
		scanf("%d", &choose);
		switch (choose){
		case 1:
			if (cfg.tWrite() == -1)
				return -1;
			break;
		case 2:
			cfg.tRead();
			break;
		case 0:
			return 0;
		default:
			return 0;
		}
	}
	system("pause");
	return 0;
}