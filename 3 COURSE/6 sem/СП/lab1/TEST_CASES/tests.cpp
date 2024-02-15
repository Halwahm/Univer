#include "tests.h"
#include <iostream>

using namespace std;

namespace tests
{
    BOOL test1(ht::HtHandle* htHandle)
    {
        // Попытка вставить элемент
        ht::Element* insertEl = new ht::Element("first", 10, "firstPayl", 10);
        ht::insert(htHandle, insertEl);

        // Попытка вставить тот же элемент снова
        BOOL insertResult = ht::insert(htHandle, insertEl);

        if (insertResult == FALSE)
            return FALSE; 

        return TRUE; 
    }

    BOOL test2(ht::HtHandle* htHandle)
    {
        // Попытка удалить элемент, который не существует в таблице
        ht::Element* element = new ht::Element("second", 16, "secondPayl", 16);

        // Попытка удалить несуществующий элемент
        BOOL removeResult = ht::removeOne(htHandle, element);

        if (removeResult == FALSE)
            return FALSE; 

        return TRUE; 
    }

    BOOL test3(ht::HtHandle* htHandle)
    {
        // Попытка обновить элемент, который не существует в таблице
        ht::Element* element = new ht::Element("third", 2, "thirdPayl", 2);

        // Попытка обновления несуществующего элемента
        BOOL updateResult = ht::update(htHandle, element, "newData", 7);

        if (updateResult == FALSE)
            return FALSE;

        return TRUE; 
    }

    BOOL test4(ht::HtHandle* htHandle)
    {
        // Попытка удалить элемент, который уже удален из таблицы
        ht::Element* element = new ht::Element("fourth", 33, "fourthPayl", 33);
        ht::insert(htHandle, element);
        ht::removeOne(htHandle, element);

        // Попытка удалить уже удаленный элемент
        BOOL removeResult = ht::removeOne(htHandle, element);

        if (removeResult == FALSE)
            return FALSE;

        return TRUE; 
    }
}