#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS TRUE
#include <winsock2.h>
#include <time.h>
#include <chrono>
#pragma comment(lib, "ws2_32.lib")

unsigned long long ntpdate();
using namespace std::chrono;
int main() {

    WSADATA wsaData;
    setlocale(LC_CTYPE, "Russian");
    if (!WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        int times[] = { 1000,3000,6000,8000,10000,12000,14000 };//тикии из методы//время между запросами
        for (int i = 0; i < 7; i++) {
            double avg = 0;
            double count = 0;
            unsigned long long cc = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            double avgCorrection = 0;
            std::cout << "sleep(" << times[i] << ")\n";
            for (int j = 0; j < 10; j++) {
                Sleep(times[i]);
                cc += times[i];
                unsigned long long ntpTime = ntpdate();
                unsigned long long ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                long long delta = ((long long)ntpTime * 1000 - (long long)cc);
                std::cout << "correction: " << abs(delta) << std::endl;
                if(ms > ntpTime*1000)
                std::cout << "ntptime-OStime: " << (ms - ntpTime * 1000) << std::endl;
                else
                {
                    std::cout << "ntptime-OStime: " << (ntpTime * 1000 - ms) << std::endl;
                }
                if (ms > ntpTime * 1000)
                avg += (double)(ms - ntpTime * 1000);
                else
                {
                    avg += (double)(ntpTime * 1000 - ms);
                }
                avgCorrection += (double)abs(delta);
                cc = cc + delta;
                count++;
            }
            std::cout << "      Avg CC - OStime: " << avg / count << std::endl;
            std::cout << "      Avg Correction: " << avgCorrection / count << std::endl;
        }
    }
    return 0;
}
char* getAddrByHost(char* hostname) {
    struct hostent* hp = gethostbyname(hostname);
    struct in_addr** p1 = NULL;

        p1 = (struct in_addr**)hp->h_addr_list;

        for (int i = 0; p1[i] != NULL; i += 1) {
            return inet_ntoa(*p1[i]);
        }
}
unsigned long long ntpdate() {

    // Хост ntp-server
    char* hostname = (char*)"vega.cbk.poznan.pl";

    // ntp порт 123
    int portno = 123;
    const int maxlen = 1024;
    int i;
    unsigned char msg[48] = { 010,0,0,0,0,0,0,0,0 };

    unsigned long buf[maxlen];
    struct protoent* proto;
    struct sockaddr_in server_addr;
    int ntpsocket; // socket
    time_t tmit;
    char* addr = getAddrByHost(hostname);
    
    //proto = getprotobyname("udp");proto->p_proto; 
    ntpsocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    std::cout << "Поключение к серверу " << addr << ":" << portno << std::endl;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(addr);
    server_addr.sin_port = htons(portno);

    i = sendto(ntpsocket, (const char*)msg, sizeof(msg), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    std::cout << "Отправка запроса\n";
    struct sockaddr socket_address;
    int fromlen = sizeof(socket_address);
    i = recvfrom(ntpsocket, (char*)buf, 48, 0, &socket_address, &fromlen);
    std::cout << "Ответ получен\n";
    tmit = ntohl((time_t)buf[4]);
    tmit -= 2208988800U-5;
    return tmit;
    char* time_str = new char[1024];
    ctime_s(time_str, 1024, &tmit);
    std::cout << "Время NTP сервера: " << time_str << std::endl;
    time_t current_time = time(0);
    time_str = new char[1024];
    ctime_s(time_str, 1024, &current_time);
    unsigned long ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    std::cout << "Время компьютера: " << time_str << std::endl;
    std::cout << "Время компьютера отличается на: " << (ms - ((unsigned long)tmit)*1000) << " миллисекунд" << std::endl;
}