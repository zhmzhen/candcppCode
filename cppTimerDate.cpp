#include <iostream>
#include <string>
#include <iomanip>
//C++ 11,
#include <chrono>
#include <ratio>
//Duration, fg, 1 minutes, count represntation =1, period precision=m,
// template <class Rep, class Period = ratio<1> >
// class duration;
/*
type 		Representation 					Period
hours 		signed integral type of at least 23 bits 	ratio<3600,1>
minutes 	signed integral type of at least 29 bits 	ratio<60,1>
seconds 	signed integral type of at least 35 bits 	ratio<1,1>
milliseconds 	signed integral type of at least 45 bits 	ratio<1,1000>
microseconds 	signed integral type of at least 55 bits 	ratio<1,1000000>
nanoseconds 	signed integral type of at least 64 bits 	ratio<1,1000000000>
 */
//
//Time Points, for epoch, it is pointer, like, 197409090910
//Clocks, system_clock, steady_clock 单调递增的稳定时钟and high_resolution_clock
// used to convert from time_t
// now() get time_point, to_time_t(), from_time_t()
void cfx_cpp_time(void) {
//http://oabinga.github.io/2016/01/06/C++%E6%97%B6%E9%97%B4%E5%BA%93%EF%BC%88%E4%BA%8C%EF%BC%89/
	// one day is 60*60*24 seconds
	std::cout << "\tcfx_cpp_time: enter" << std::endl;
	//C++
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	std::cout << "\tToday is           " << std::put_time(&tm, "%c %Z") <<'\n';

//Duration, first, it is 单位，然后是多少单位，下面是单位是天，两个天
	std::chrono::duration<int,std::ratio<60*60*24, 1>> one_day(2);
//timepoint: system_clock
	std::chrono::system_clock::time_point today = std::chrono::system_clock::system_clock::now();
	std::chrono::system_clock::time_point tomorrow_after = today + one_day;

	std::time_t tt;
	tt = std::chrono::system_clock::to_time_t ( today );
	std::cout << "\ttoday is: " << ctime(&tt);
	tt = std::chrono::system_clock::to_time_t ( tomorrow_after);
	std::cout << "\ttomorrow_after will be: " << ctime(&tt);
//timepoint steady_clock
	using namespace std::chrono;
	steady_clock::time_point t1 = steady_clock::now();
	high_resolution_clock::time_point th1 = high_resolution_clock::now();
	std::cout << "printing out 1000 stars...\n";
  	//for (int i=0; i<100000; ++i) std::cout << "*";
	int j=0;
  	for (int i=0; i<100000; ++i) j++;
  	std::cout << std::endl;
	high_resolution_clock::time_point th2 = high_resolution_clock::now();
	steady_clock::time_point t2 = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout << "It took me s: " << time_span.count() << " seconds.";
	duration<double> time_span_h = duration_cast<duration<double>>(th2 - th1);
	std::cout << "\nIt took me h: " << time_span_h.count() << " seconds.";
	std::cout << "\nIt took me hmc: " << std::chrono::duration_cast<std::chrono::microseconds>(th2 -th1).count() << " seconds.";

	std::cout << "\tcfx_cpp_time: exit" << std::endl;
	return;
}

//ref
// http://oabinga.github.io/2016/01/06/C++%E6%97%B6%E9%97%B4%E5%BA%93%EF%BC%88%E4%B8%80%EF%BC%89/
//
void cfx_time(void)
{
/*
 *
struct tm
{
    int tm_sec;  秒，正常范围0-59， 但允许至61, C99(C++11)改为60
    int tm_min;  分钟，0-59
    int tm_hour; 小时， 0-23
    int tm_mday; 日，即一个月中的第几天，1-31
    int tm_mon;  月， 从一月算起，0-11，1+tm_mon
    int tm_year; 年， 从1900至今已经多少年， 1900+tm_year
    int tm_wday; 星期，一周中的第几天， 从星期日算起，0-6
    int tm_yday; 从今年1月1日到目前的天数，范围0-365，其中0代表1月1日，1代表1月2日，以此类推
    int tm_isdst;  夏令时标识符，tm_isdst>0，实行夏令时的时候；tm_isdst=0, 不实行夏令时的进候；tm_isdst<0, 表示未知
};

struct timeval {
  long tv_sec;   //秒
  long tv_usec;  //微秒
} timeval;
 */
	std::cout << "\tcfx: enter" << std::endl;
	// since 1970 1/1 0s UTC seconds
	time_t timer;
	std::cout << "\tcfx: since 1970 1/1 0s UTC seconds = " << time(&timer) << std::endl;
	//time_t to tm
	//  g_tm = gmtime(&timer);
	//  time_t to local time tm
	struct tm* loc_timeinfo = localtime(&timer);
	std::cout << "\tcfx: localtime and date:  = " << asctime(loc_timeinfo) << std::endl;
	//clock number / 1000 is second
	clock_t start, finish;
	start = clock();
	finish = clock();
	std::cout << "\tcfx: start= " << start << std::endl;
	std::cout << "\tcfx: finish= " << finish << std::endl;

	std::cout << "\tcfx: exit " << std::endl;
	return;
}

int main() {
	std::cout << "main: enter" << std::endl;
	cfx_time();
	cfx_cpp_time();
	std::cout << "main: exit" << std::endl;
	return 0;
}
