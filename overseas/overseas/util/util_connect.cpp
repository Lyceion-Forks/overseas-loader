/*      util_connect.cpp
 *
 *
 *
 */

#include "includes.h"
#include "util.h"
#include "util_connect.h"


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t writedata_download(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

std::string Connect::sendGet(std::string url, std::string data)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    
    url = url + "?" + data;
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
    }
    
    return readBuffer;
}

bool Connect::downloadFile(std::string url, std::string outPath)
{
    FILE* fp;
    CURL* curl = curl_easy_init();
    
    if (curl)
    {
        fp = fopen(outPath.c_str(), "wb");
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata_download);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        fclose(fp);
    }
    
    // if the file was downloaded correctly then
    // it should exist therefore it'll return true
    return Util::doesFileExist(outPath);
}
