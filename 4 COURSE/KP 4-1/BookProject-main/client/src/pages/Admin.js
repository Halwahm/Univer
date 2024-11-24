import React, { useState, useEffect } from "react";
import { Container, Button, Tabs, Tab } from "react-bootstrap";
import DataTable from "../components/DataTable";
import {
  fetchBooks,
  deleteBook,
  editBook,
  fetchGanre,
  createGenre,
  delGanre,
  fetchTags,
  createTag,
  delTag,
  fetchAuthor,
  createAuthor,
  delAuthor,
} from "../http/bookAPI";
import { featchUsers, deleteUser, update } from "../http/userAPI";
import CreateBook from "../components/modals/CreateBook";
import CreateGanre from "../components/modals/CreateGanre";
import CreateTag from "../components/modals/CreateTag";
import CreateAuthor from "../components/modals/CreateAuthor";
import UpdateUser from "../components/modals/UpdateUser";
import EditBook from "../components/modals/EditBook";

const Admin = () => {
  const [data, setData] = useState([]);
  const [key, setKey] = useState("books");
  const [schema, setSchema] = useState([]);
  const [actions, setActions] = useState([]);
  const [modalState, setModalState] = useState({}); // Для управления модальными окнами

  // Функция для загрузки данных
  const loadData = async (key) => {
    try {
      let result;
      switch (key) {
        case "books":
          result = await fetchBooks(1);
          setSchema([
            { label: "ID", field: "ID" },
            { label: "Название", field: "BOOK_NAME" },
            { label: "Описание", field: "BOOK_DESCRIPTION" },
          ]);
          setActions([
            {
              label: "Редактировать",
              variant: "warning",
              onClick: (row) => setModalState({ type: "editBook", data: row }),
            },
            {
              label: "Удалить",
              variant: "danger",
              onClick: (row) => handleDelete(row, "book"),
            },
          ]);
          setData(result.books);
          break;

        case "users":
          result = await featchUsers(1);
          setSchema([
            { label: "ID", field: "ID" },
            { label: "Имя", field: "USER_NAME" },
            { label: "Email", field: "EMAIL" },
          ]);
          setActions([
            {
              label: "Редактировать",
              variant: "warning",
              onClick: (row) => setModalState({ type: "editUser", data: row }),
            },
            {
              label: "Удалить",
              variant: "danger",
              onClick: (row) => handleDelete(row, "user"),
            },
          ]);
          setData(result.users);
          break;

        case "genres":
          result = await fetchGanre(1);
          setSchema([
            { label: "ID", field: "ID" },
            { label: "Жанр", field: "GENRE_NAME" },
          ]);
          setActions([
            {
              label: "Удалить",
              variant: "danger",
              onClick: (row) => handleDelete(row, "genre"),
            },
          ]);
          setData(result.genres);
          break;

        case "tags":
          result = await fetchTags(1);
          setSchema([
            { label: "ID", field: "ID" },
            { label: "Тег", field: "TAG_NAME" },
          ]);
          setActions([
            {
              label: "Удалить",
              variant: "danger",
              onClick: (row) => handleDelete(row, "tag"),
            },
          ]);
          setData(result.tags);
          break;

        case "authors":
          result = await fetchAuthor(1);
          setSchema([
            { label: "ID", field: "ID" },
            { label: "Автор", field: "AUTHOR_NAME" },
          ]);
          setActions([
            {
              label: "Удалить",
              variant: "danger",
              onClick: (row) => handleDelete(row, "author"),
            },
          ]);
          setData(result.authors);
          break;

        default:
          break;
      }
    } catch (error) {
      console.error("Ошибка загрузки данных:", error);
    }
  };

  // Обработчик удаления
  const handleDelete = async (row, type) => {
    try {
      switch (type) {
        case "book":
          await deleteBook(row.ID);
          break;
        case "user":
          await deleteUser(row.ID);
          break;
        case "genre":
          await delGanre(row.ID);
          break;
        case "tag":
          await delTag(row.ID);
          break;
        case "author":
          await delAuthor(row.ID);
          break;
        default:
          break;
      }
      loadData(key); // Обновить данные
    } catch (error) {
      console.error(`Ошибка при удалении ${type}:`, error);
    }
  };

  // Обновляем данные при смене вкладки
  useEffect(() => {
    loadData(key);
  }, [key]);

  return (
    <Container>
      <h1>Админ Панель</h1>
      <div className="mb-3">
        {key === "books" && (
          <Button
            variant="primary"
            onClick={() => setModalState({ type: "createBook" })}
          >
            Добавить книгу
          </Button>
        )}
        {key === "genres" && (
          <Button
            variant="primary"
            onClick={() => setModalState({ type: "createGenre" })}
          >
            Добавить жанр
          </Button>
        )}
        {key === "tags" && (
          <Button
            variant="primary"
            onClick={() => setModalState({ type: "createTag" })}
          >
            Добавить тег
          </Button>
        )}
        {key === "authors" && (
          <Button
            variant="primary"
            onClick={() => setModalState({ type: "createAuthor" })}
          >
            Добавить автора
          </Button>
        )}
      </div>
      <Tabs
        id="admin-tabs"
        activeKey={key}
        onSelect={(k) => setKey(k)}
        className="mb-3"
      >
        <Tab eventKey="books" title="Книги">
          <DataTable schema={schema} data={data} actions={actions} />
        </Tab>
        <Tab eventKey="users" title="Пользователи">
          <DataTable schema={schema} data={data} actions={actions} />
        </Tab>
        <Tab eventKey="genres" title="Жанры">
          <DataTable schema={schema} data={data} actions={actions} />
        </Tab>
        <Tab eventKey="tags" title="Теги">
          <DataTable schema={schema} data={data} actions={actions} />
        </Tab>
        <Tab eventKey="authors" title="Авторы">
          <DataTable schema={schema} data={data} actions={actions} />
        </Tab>
      </Tabs>

      {/* Модальные окна */}
      {modalState.type === "createBook" && (
        <CreateBook
          show={true}
          onHide={() => setModalState({})}
          onSave={() => loadData("books")}
        />
      )}
      {modalState.type === "editBook" && (
        <EditBook
          show={true}
          bookData={modalState.data}
          onHide={() => setModalState({})}
          onSave={() => loadData("books")}
        />
      )}
      {modalState.type === "createGenre" && (
        <CreateGanre
          show={true}
          onHide={() => setModalState({})}
          onSave={() => loadData("genres")}
        />
      )}
      {modalState.type === "createTag" && (
        <CreateTag
          show={true}
          onHide={() => setModalState({})}
          onSave={() => loadData("tags")}
        />
      )}
      {modalState.type === "createAuthor" && (
        <CreateAuthor
          show={true}
          onHide={() => setModalState({})}
          onSave={() => loadData("authors")}
        />
      )}
      {modalState.type === "editUser" && (
        <UpdateUser
          show={true}
          user={modalState.data}
          onHide={() => setModalState({})}
          onSave={() => loadData("users")}
        />
      )}
    </Container>
  );
};

export default Admin;
