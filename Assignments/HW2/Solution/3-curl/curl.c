#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char **argv)
{
        FILE *links = fopen(argv[1], "r");
        char line[256];
        while (fgets(line, sizeof(line), links))
        {
                pid_t f = fork();
                if (f == 0)
                {
                        CURL *curl = curl_easy_init();
                        if (curl)
                        {
                                line[strlen(line)-1] = '\0';
                                int i = strlen(line);
                                while (line[i] != '/')
                                        i--;
                                i++;
                                FILE *fp = fopen(line+i, "wb");
                                curl_easy_setopt(curl, CURLOPT_URL, line);
                                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
                                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

                                CURLcode res = curl_easy_perform(curl);
                                if (res != CURLE_OK)
                                        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                                curl_easy_cleanup(curl);
                                fclose(fp);
                                exit(0);
                        }
                }
        }

        while (wait(NULL) > 0);
        fclose(links);
        return 0;
}
