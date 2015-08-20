#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <jni.h>
#include <jni_md.h>

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_mf_Reader_init(JNIEnv *, jobject, jstring);
#ifdef __cplusplus
}
#endif

JNIEXPORT void JNICALL Java_com_mf_Reader_init(JNIEnv *env, jobject obj, jstring d) {
	jclass cls = (*env)->GetObjectClass(env, obj);
	jmethodID mid = (*env)->GetMethodID(env, cls, "callback",
			"(Ljava/lang/String;)V");

	const char *device = (*env)->GetStringUTFChars(env, d, 0);
	struct input_event ev[64];
	int rd, size = sizeof(struct input_event), result = 0, fevdev = -1;
	char name[256] = "Unknown";

	char code[64] = { 0 };
	char *K[155] = {
			"", "", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
			"", "", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]",
			"", "", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "~",
			"", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "", "*",
			"", " ", "", "", "", "", "", "", "", "", "", "", "", "", "", "7",
			"8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "", "",
			"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""
	};

	fevdev = open(device, O_RDONLY);
	if (fevdev == -1) {
		printf("Failed to open RFID reader.\n");
		exit(1);
	}

	printf("Exclusive access: ");
	result = ioctl(fevdev, EVIOCGRAB, 1);
	printf("%s\n", (result == 0) ? "SUCCESS" : "FAILURE");

	while (1) {
		if ((rd = read(fevdev, ev, size * 64)) < size)
			break;

		if (ev[1].value == 1 && ev[1].type == 1) {
			if (ev[1].code == 28) {
				(*env)->CallVoidMethod(env, obj, mid, (*env)->NewStringUTF(env, code));
				*(code) = 0;
			} else {
				sprintf(code + strlen(code), "%s", K[ev[1].code]);
			}
		}
	}

	result = ioctl(fevdev, EVIOCGRAB, 1);
	close(fevdev);

	return;
}
