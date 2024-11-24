import React, { useState, useEffect } from "react";
import { Container, Button, Tabs, Tab, Alert } from "react-bootstrap";
import CreateBook from "../components/modals/CreateBook";
import EditBook from "../components/modals/EditBook";
import { fetchBooksByAuthor, deleteBook } from "../http/bookAPI";
import DataTable from "../components/DataTable";
import { schemaBook } from "../utils/shemaTable";
import { observer } from "mobx-react-lite";

const AuthorPanel = observer(() => {
    const [bookShow, setBookShow] = useState(false); // Модальное окно для добавления книги
    const [editShow, setEditShow] = useState(false); // Модальное окно для редактирования книги
    const [books, setBooks] = useState([]); // Список книг
    const [page, setPage] = useState(1); // Текущая страница
    const [totalPages, setTotalPages] = useState(1); // Количество страниц
    const [alertShow, setAlertShow] = useState(false); // Показывать ли сообщение об ошибке
    const [variant, setVariant] = useState("success"); // Тип сообщения
    const [alertText, setAlertText] = useState(""); // Текст сообщения
    const [editData, setEditData] = useState(null); // Данные книги для редактирования

    const userId = localStorage.getItem("id"); // ID текущего пользователя

    // Загрузка книг автора
    const loadBooks = async () => {
        try {
            const result = await fetchBooksByAuthor(userId, page); // Запрос на сервер
            setBooks(result.books); // Устанавливаем книги
            setTotalPages(result.totalPages); // Устанавливаем общее количество страниц
        } catch (error) {
            console.error("Ошибка при загрузке книг:", error);
            setAlertShow(true);
            setVariant("danger");
            setAlertText("Не удалось загрузить книги.");
        }
    };

    // Загрузка книг при изменении страницы
    useEffect(() => {
        loadBooks();
    }, [page]);

    // Удаление книги
    const handleDelete = async (id) => {
        try {
            await deleteBook(id); // Удаляем книгу
            loadBooks(); // Обновляем список книг
            setAlertShow(true);
            setVariant("success");
            setAlertText("Книга успешно удалена.");
        } catch (error) {
            console.error("Ошибка при удалении книги:", error);
            setAlertShow(true);
            setVariant("danger");
            setAlertText("Не удалось удалить книгу.");
        }
    };

    // Открытие модального окна для редактирования книги
    const handleEdit = (book) => {
        setEditData(book); // Устанавливаем данные для редактирования
        setEditShow(true); // Показываем модальное окно
    };

    return (
        <Container>
            <h1>Панель автора</h1>
            {alertShow && (
                <Alert
                    variant={variant}
                    className="mt-3"
                    onClose={() => setAlertShow(false)}
                    dismissible
                >
                    {alertText}
                </Alert>
            )}
            <Button variant="primary" onClick={() => setBookShow(true)}>
                Добавить книгу
            </Button>
            {/* Компонент для добавления книги */}
            <CreateBook
                show={bookShow}
                onHide={() => setBookShow(false)}
                onComplete={loadBooks} // Перезагрузка списка книг после добавления
            />
            {/* Компонент для редактирования книги */}
            <EditBook
                show={editShow}
                onHide={() => setEditShow(false)}
                bookData={editData} // Передаем данные для редактирования
                onEditComplete={() => {
                    setEditShow(false);
                    loadBooks(); // Перезагрузка списка книг после редактирования
                }}
            />
            {/* Таблица книг */}
            <Tabs defaultActiveKey="books" className="mt-3">
                <Tab eventKey="books" title="Мои книги">
                    <DataTable
                        schema={schemaBook} // Схема таблицы
                        data={books} // Данные книг
                        table="books"
                        actions={[
                            {
                                label: "Редактировать",
                                onClick: handleEdit, // Открытие окна редактирования
                            },
                            {
                                label: "Удалить",
                                onClick: (row) => handleDelete(row.ID), // Удаление книги
                            },
                        ]}
                    />
                </Tab>
            </Tabs>
        </Container>
    );
});

export default AuthorPanel;
