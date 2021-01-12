#ifndef ICODE_REFRESH_NUMBER_DICT_H
#define ICODE_REFRESH_NUMBER_DICT_H

#include "icode_visitor.h"

/**
 * @brief 更新pcompi中的m_icode_number_dict & m_functions两个变量内容
 *
 *
 */
class icode_refresh_number_dict : public icode_visitor
{
public:
    icode_refresh_number_dict();
    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


};

#endif // ICODE_REFRESH_NUMBER_DICT_H
