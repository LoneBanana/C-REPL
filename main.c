#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#define MAX_SIZE 2048

/*

Goal: Create C-REPL --> idea is that, for quick testing of certain features it is useful; we don't need to type things like main method and whatnot; we can simply type in the code and watch it function as intended;

*/



int main(void) {

	char template[] = "/tmp/tmp.XXXXXX";
	int fd = mkstemp(template); //Secure temporary file so no collisions;
	
	if (fd == -1) {
		perror("Bad File Descriptor");
		return 1;
		}
	
	FILE *fp = fdopen(fd, "a");
	if (!fp) {
		perror("Unable to open in append mode, per file descriptor");	
		return 1;
		}
	char *headBuffer[] = {
		"<assert.h>",
		"<complex.h>",
		"<ctype.h>",
		"<errno.h>",
		"<fenv.h>",
		"<float.h>",
		"<inttypes.h>",
		"<iso646.h>",
		"<limits.h>",
		"<locale.h>",
		"<math.h>",
		"<setjmp.h>",
		"<signal.h>",
		"<stdarg.h>",
		"<stdatomic.h>",
		"<stdckdint.h>",
		"<stdcountof.h>",
		"<stddef.h>",
		"<stdint.h>",
		"<stdio.h>",
		"<stdlib.h>",
		"<string.h>",
		"<tgmath.h>",
		"<time.h>",
		"<wchar.h>",
		"<wctype.h>"
		};
	for (register size_t i = 0; i < sizeof(headBuffer)/sizeof(*headBuffer); i++) {
		fputs("#include ", fp);
		fputs(headBuffer[i], fp);
		fputc('\n', fp);
		}
	fputs("int main(int argc, char **argv) {\n", fp);	
	
	char textBuffer[MAX_SIZE] = {0};	
	//Don't use fgets here, because fgets stops after \n or EOF
	
	fread(textBuffer, 1, MAX_SIZE - 1, stdin);
	
	fputs(textBuffer, fp); //Used because it puts until we reach null terminator, so super easy: no need for strlen
	
	fputs("return 0;\n}", fp);	
	fclose(fp);
	char cmdBuffer[100] = {0};
	snprintf(cmdBuffer, sizeof(cmdBuffer)-1, "cc -x c %s -o %s", template, template);
	system(cmdBuffer);
	system(template);
	
	unlink(template);	

	return 0;
	}
