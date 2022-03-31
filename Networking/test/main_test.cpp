#include <iostream>
#include <vector>



std::vector<std::string> split_header (std::string s) {
    size_t pos_start = 0, pos;
    std::string token;
    std::vector<std::string> res;

    if ((pos = s.find (":")) != std::string::npos) {
        if (pos + 2 < s.size() && (s[pos+1] == '\t' || s[pos+1] == ' ') &&!(s[pos+2] == '\t' || s[pos+2] == ' '))
        {
            token = s.substr (0, pos);
            res.push_back (token);
            token = s.substr (pos+2,s.size() - pos);
            res.push_back (token);
        }
    }
    return res;
}
 
void test(std::string test)
{
     std::vector<std::string> vec=  split(test);
     for (size_t i = 0; i <vec.size() ; i++)
     {
         std::cout << "{" << vec[i] << "}" << std::endl;
     }
}

 int main()
 {
   test("Host: www.bing.com");
   std::cout << "=====" << std::endl;
   test("User-Agent: curl/7.54.0");
     std::cout << "=====" << std::endl;
   test("Accept: */*");
      std::cout << "=====" << std::endl;
   test("Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7");
      std::cout << "=====" << std::endl;
   test("User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; fr; rv:1.9.2.8) Gecko/20100722 Firefox/3.6.8");
      std::cout << "=====" << std::endl;
    test("last-modified: Sun, 07 Nov 2021 21:49:20 GMT"); 
 }
