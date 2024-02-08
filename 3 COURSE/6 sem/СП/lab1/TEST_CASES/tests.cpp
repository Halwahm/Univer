#include "tests.h"
#include <iostream>

using namespace std;

namespace tests
{
    BOOL test1(ht::HtHandle* htHandle)
    {
        // Попытка вставить элемент
        ht::Element* insertEl = new ht::Element("test1", 6, "test1", 6);

        BOOL insertResult = ht::insert(htHandle, insertEl);

        // Ожидается, что повторная попытка вставки вернет FALSE
        if (insertResult == FALSE)
            return TRUE; // Ошибка: повторная вставка выполнена успешно

        return FALSE; // Негативный сценарий не произошел
    }

    BOOL test2(ht::HtHandle* htHandle)
    {
        // Попытка удалить элемент, который не существует в таблице
        ht::Element* element = new ht::Element("test2", 6, "test2", 6);

        BOOL removeResult = ht::removeOne(htHandle, element);

        // Ожидается, что попытка удаления несуществующего элемента вернет FALSE
        if (removeResult == FALSE)
            return TRUE; // Ошибка: удаление выполнено, хотя не должно было быть

        return FALSE; // Негативный сценарий не произошел
    }

    BOOL test3(ht::HtHandle* htHandle)
    {
        // Попытка вставить элемент, который уже существует в таблице
        ht::Element* element = new ht::Element("test3", 6, "test3", 6);
        ht::insert(htHandle, element);

        BOOL insertResult = ht::insert(htHandle, element);

        // Ожидается, что попытка вставить существующий элемент вернет FALSE
        if (insertResult == FALSE)
            return TRUE; // Ошибка: вставка выполнена успешно, хотя не должно было быть

        return FALSE; // Негативный сценарий не произошел
    }

    BOOL test4(ht::HtHandle* htHandle)
    {
        // Попытка удалить элемент, который уже удален из таблицы
        ht::Element* element = new ht::Element("test4", 6, "test4", 6);
        ht::insert(htHandle, element);
        ht::removeOne(htHandle, element);

        BOOL removeResult = ht::removeOne(htHandle, element);

        // Ожидается, что попытка удалить уже удаленный элемент вернет FALSE
        if (removeResult == FALSE)
            return TRUE; // Ошибка: удаление выполнено успешно, хотя не должно было быть

        return FALSE; // Негативный сценарий не произошел
    }
}