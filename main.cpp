#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <exception>
#include <string>
#include <cerrno>


using std::cout;
using std::endl;
using std::exception;
using std::string;


class GenericException : public exception 
{
    private:    
        string msg;
    
    public:
        GenericException(const string &ex_msg) : msg(ex_msg) 
        {
             /** **/     
        }

        const char* what() const throw() 
        {
            return msg.c_str(); 
        }
};

typedef struct monitor_info_struct
{
  private:
    float monitor_hight;
    float monitor_width;
    float diagonal;

    int pixles_width;
    int pixles_hight;

    int pixles_per_inch;

public:
    monitor_info_struct(int px_width, int px_hight, float mon_diagonal) : 
        monitor_hight(0.0f), monitor_width(0.0f),
        diagonal(mon_diagonal), pixles_width(px_width), 
        pixles_hight(px_hight), pixles_per_inch(0)        
    {
        calculateMonitorValues();
    }

    void calculateMonitorValues()
    {

    }

    void print(bool verbose = false)
    {
        cout << "Monitor hight:    " << monitor_hight << endl;
        cout << "Monitor width:    " << monitor_hight << endl;
        cout << "Monitor diagonal: " << diagonal << endl;
        cout << "Pixles hight:     " << pixles_hight << endl;
        cout << "Pixles width:     " << pixles_width << endl;
    }
} MonitorInfo;

MonitorInfo checkAndParseArgs(int argc, char *argv[])
{
    int hight = 0, width = 0;
    float diagonal = 0.0f;

    if(argc != 4)
        throw GenericException("Error invalid number of arguments!!!");

    errno = ENOENT;

    diagonal = strtof(argv[3], NULL);
    hight    = strtol(argv[2], NULL, 0);
    width    = strtol(argv[1], NULL, 0);

    if(errno != ENOENT || diagonal == 0.0f || hight == 0 || width == 0)
        throw GenericException("Error invalid input format!!!");

    return MonitorInfo(width, hight, diagonal);
}

/*
    cout << "lool" << endl;
*/



int main(int argc, char *argv[])
{
    MonitorInfo *mon_nfo;

    try
    {
        mon_nfo = new MonitorInfo(checkAndParseArgs(argc, argv));
    }
    catch(exception &exc) 
    {
        cout << exc.what() << endl;
        exit(-1);
    }

    mon_nfo->print();

    return 0;
}
