#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct f_f t[] = {

#include "ucb/sinf.h"
#include "sanity/sinf.h"
};

int main(void)
{
	float y;
	float d;
	int e, i, err = 0;
	struct f_f *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = sinf(p->x);
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s sinf(%a)==%a except: want %s", rstr(p->r), p->x, p->y, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperrf(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s sinf(%a) want %a got %a ulperr %.3f = %a + %a\n",
				rstr(p->r), p->x, p->y, y, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}