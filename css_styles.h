#ifndef CSS_TAGS_H_
#define CSS_TAGS_H_

#define CSS_RULE(selector) SCOPE(fprintf(fp, "%s {", selector), fputs("}", fp))
#define CSS_PROP(name, value) fprintf(fp, "  %s: %s;\n", name, value)

#endif