#ifndef DIS_KEYWORDS_H
#define DIS_KEYWORDS_H
#include <string>
#include <map>
//typedef std::string (* DIS_FUNC_PTR) (std::string mbin, unsigned curr_addr, unsigned& labeled_abs_addr);
typedef std::string (* DIS_FUNC_PTR) (class dis8051*dis, std::string mbin, unsigned curr_addr);

int load_dis_keywords(std::map<unsigned, DIS_FUNC_PTR> &keys);



#endif // DIS_KEYWORDS_H


