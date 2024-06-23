#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	const char *note;
	int offset;
} NoteOffset;

int find_offset(NoteOffset *offsets, int len, char *note) {
	for (int i = 0; i < len; i++) {
		if (strcasecmp(offsets[i].note, note) == 0) {
			return offsets[i].offset;
		}
	}
	return -1;
}

int main(int argc, char *argv[]) {
	// starting from high-E: EBGDAE 
	int octave = 12;
	int string_offsets[] = {7, 2, 10, 5, 0, 7};
	NoteOffset offsets[] = {
		{"a", 0},
		{"a#", 1},
		{"bb", 1},
		{"b", 2},
		{"c", 3},
		{"c#", 4},
		{"db", 4},
		{"d", 5},
		{"d#", 6},
		{"eb", 6},
		{"e", 7},
		{"f", 8},
		{"f#", 9},
		{"gb", 9},
		{"g", 10},
		{"g#", 11},
		{"ab", 11},
	};
	int len = sizeof(offsets) / sizeof(offsets[0]);
	// Fret values

	int strings = 6;
	int frets = 12;

	if (argc < 2) {
		fprintf(stderr, "Error: requires a note argument (e.g c#, f, b)\n");
		return 1;
	}

	char *note = argv[1];
	int offset = find_offset(offsets, len, note);

	if (offset < 0) {
		fprintf(stderr, "Error: argument needs to be a note (c, c#, db)\n");
		return 1;
	}

	const char *su = "|";
	const char *sp = "x";
	const char *u = "---|";
	const char *p = "-x-|";
	const char *cnt = "  %d ";
	const char *ddcnt = "  %d";
	for (int st = 0; st < strings; st++) {
		if (string_offsets[st] == offset) {
			printf("%s", sp);
		} else {
			printf("%s", su);
		}
		for (int o = 1; o < octave + 1; o++) {
			int pressed = (o + string_offsets[st]) % octave == offset;
			if (pressed) {
				printf("%s", p);
			}
			else {
				printf("%s", u);
			}

		}
		printf("\n");
	}
	for (int o = 0; o < octave; o++) {
		int op = o + 1;
		if (op >= 10) {
			printf(ddcnt, op);
		} else {
			printf(cnt, op);
		}
	}
	printf("\n");
}
