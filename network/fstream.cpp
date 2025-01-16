#include <iostream>
#include <fstream>
#include <error.h>
#include <sys/time.h>

int 
main ()
{
	struct timeval start_t, end_t;
	gettimeofday(&start_t, NULL);
	std::ofstream output_file_("/root/others/ccppCode/network/cfx.t", std::ios_base::binary);
	gettimeofday(&end_t, NULL);
	long duration_t = (end_t.tv_sec - start_t.tv_sec) * 1000 * 1000 + end_t.tv_usec - start_t.tv_usec;
	std::cout << " the open duration_t:" << duration_t << std::endl;
	gettimeofday(&start_t, NULL);
	output_file_.close();
	gettimeofday(&end_t, NULL);
	duration_t = (end_t.tv_sec - start_t.tv_sec) * 1000 * 1000 + end_t.tv_usec - start_t.tv_usec;
	std::cout << " the close duration_t:" << duration_t << std::endl;
	return 0;
}
