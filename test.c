#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "html_tags.h"
#include "css_styles.h"
#include "generate.c"
typedef struct {
  char *user_name;
  int task_count;
  char **tasks;
} user_tasks;

void user_tasks_html(FILE *fp, void *data) {
   user_tasks *tasks = (user_tasks *)data;
  {
    DOCTYPE;
    HTML("en") {
      HEAD() {
        META("charset='utf-8'");
        META("name='viewport' "
             "content='width=device-width, initial-scale=1'");
        TITLE("Index page");
        META("name='description' content='Description'");
        META("name='author' content='Author'");
        META("property='og:title' content='Title'");
        LINK("rel='icon' href='/favicon.svg' type='image/svg+xml'");
        LINK("rel='stylesheet' href='styles.css'");
      }
      BODY("") {
        DIV("id='main'") {
          H1("id='title'") { _("Hello %s", tasks->user_name); }
          P("Your tasks for today:");
          if (tasks->task_count > 0) {
            UL("id='list' class='default'") {
              for (int i = 0; i < tasks->task_count; i++) {
                LI("class='default'") {
                  _("Task %d: %s", i + 1, tasks->tasks[i]);
                }
              }
            }
          }
        }
      }
      SCRIPT("js/main.js");
    }
  }
}

void user_tasks_css(FILE *fp, void *data) {
    (void)data;  // Так как CSS статичный, пока игнорируем `data`
    
    CSS_RULE("body") {
        CSS_PROP("background-color", "lightgray");
        CSS_PROP("font-family", "Arial, sans-serif");
    }
    CSS_RULE("#main") {
        CSS_PROP("width", "80%");
        CSS_PROP("margin", "0 auto");
    }
    CSS_RULE("#title") {
        CSS_PROP("font-size", "25px");
        CSS_PROP("text-align", "center");
        CSS_PROP("color", "#333");
    }
    CSS_RULE("#list") {
        CSS_PROP("display", "flex");
        CSS_PROP("flex-direction", "column");
        CSS_PROP("gap", "20px");
    }
}


void user_tasks_js(FILE *fp, void *data) {
    
}



int main() {
  user_tasks data;
  {
    data.user_name = "Vanya";
    data.task_count = 4;
    data.tasks = calloc(data.task_count, sizeof(char *));
    {
      data.tasks[0] = "Make C project";
      data.tasks[1] = "Make CSS-battle";
      data.tasks[2] = "Play tanki";
      data.tasks[3] = "Make js";
    }
  }
  printf("Generating HTML for user: %s\n",  data.user_name);
  generate(user_tasks_html, "./tasks/vanya.html", &data);
  generate(user_tasks_css, "./tasks/styles.css", &data);

  return 0;
}