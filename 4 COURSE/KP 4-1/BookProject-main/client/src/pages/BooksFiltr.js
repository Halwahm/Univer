import { observer } from "mobx-react-lite";
import React, { useState, useEffect, useMemo } from "react";
import { Tabs, Tab, Pagination, Row, Container } from "react-bootstrap";
import { fetchBookSearch } from "../http/bookAPI";
import BookItem from "../components/BookItem";
import BooksList from "../components/BooksList";
import { useContext } from "react";
import { Context } from "../index";
import { useNavigate, useLocation, useParams } from "react-router-dom";


const BooksFiltr = observer(() => {
  const { book } = useContext(Context);
  const navigate = useNavigate();
  const { sort } = useParams();
  const location = useLocation();

  let [alertshow, setAlertshow] = React.useState(false);
  const [variant, setVariant] = React.useState('success');
  const [alertText, setAlertText] = React.useState('');


  const [totalPages, setTotalPages] = useState(0);
  const [marks, setMarks] = useState([]);
  const [loading, setLoading] = useState(false);
  const { id } = useParams();
  const [searchTerm, setSearchTerm] = useState('');
  const [filterParams, setFilterParams] = useState({ tags: [], genres: [], authors: [], series: [] });
  const path = location.pathname.split('/').slice(1)[0];
  console.log(path);
  console.log(sort);
  const setFiltr = () => {
    switch (path) {
      case 'genre': {
        const genre = { ID: id, GENRE_NAME: sort };
        const genres = [...filterParams.genres]
        genres.push(genre);
        setFilterParams({ ...filterParams, genres: [genre] });
        break;
      }
      case 'author': {
        const author = { ID: id, AUTHOR_NAME: sort };
        const authors = [...filterParams.authors]
        authors.push(author);
        setFilterParams({ ...filterParams, authors: [author] });
        break;
      }
      case 'tag': {
        const tag = { ID: id, TAG_NAME: sort };
        const tags = [...filterParams.tags]
        tags.push(tag);
        setFilterParams({ ...filterParams, tags: [tag] });
        break;
      }
      default: {
        setSearchTerm(sort);
      }
        localStorage.setItem('filterParams', JSON.stringify(filterParams));
        localStorage.setItem('searchTerm', JSON.stringify(searchTerm));
    }
  }

  //Запускаем фильтрацию при загрузке страницы
  const [page, setPage] = useState(null);
  useEffect(() => {
    setFiltr();
    setPage(1);
  }, []);


  useEffect(() => {
    const load = async () => {
      setLoading(true);
      try {
        if (page > 0) {
          if (
            filterParams.authors.length > 0 ||
            filterParams.genres.length > 0 ||
            filterParams.tags.length > 0 ||
            searchTerm
          ) {
            const data = await fetchBookSearch(page, searchTerm, filterParams);
            setMarks(data.books);
            setTotalPages(data.totalPages);
          } else {
            setMarks([]);
          }
        }
      } catch (error) {
        console.log(error);
        setAlertshow(true);
        setVariant('danger');
        setAlertText('Произошла ошибка: ' + error.response.data.message);
      } finally {
        setLoading(false);
      }
    }
    load();
  }, [page]);

  if (loading) {
    return <div>Загрузка...</div>;
  }

  if (marks.length === 0) {
    return <div>Нет результатов</div>;
  }


  if (marks.length === 0) {
    return <div>Нет результатов</div>;
  }

  return (
    <Container>
      <Row className="d-flex justify-content-center">
        <h1>Поиск по запросу: {sort}</h1>
      </Row>
      <Row>
        {marks.map((mark) => (
          <BookItem key={mark.id} book={mark} />
        ))}
      </Row>
      <Pagination>
        <Pagination.First disabled={page === 1} onClick={() => setPage(1)} />
        <Pagination.Prev disabled={page === 1} onClick={() => setPage(page - 1)} />
        <Pagination.Item active>{page}</Pagination.Item> {/* Элемент для отображения номера страницы */}
        <Pagination.Next
          disabled={page === Math.ceil(totalPages)}
          onClick={() => setPage(page + 1)}
        />
        <Pagination.Last
          disabled={page === Math.ceil(totalPages)}
          onClick={() => setPage(Math.ceil(totalPages))}
        />
      </Pagination>

    </Container>
  );
})


export default BooksFiltr;
