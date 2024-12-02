import React, { useContext, useEffect, useState } from "react";
import { Col, Container, Row, Image, Card, Button, ListGroup, Nav, Alert } from "react-bootstrap";
import { useParams } from "react-router-dom";
import { observer } from "mobx-react-lite";
import { Context } from "../index";
import {
  fetchOneBook,
  getBookAuthor,
  getBookIDGenre,
  getBookIDTag,
  getBookAvarageRaiting,
} from "../http/bookAPI";
import { getBoomarkId, addMarks } from "../http/userAPI";
import { formatDate } from "../utils/const";
import ReadBook from "../components/ReadBook";
import Feedback from "../components/Feedback";

const BookPage = observer(() => {
  const { currentBook } = useContext(Context);
  const { user } = useContext(Context);
  const { id } = useParams();

  const [loading, setLoading] = useState(true);
  const [raiting, setRaiting] = useState(0);
  const [author, setAuthor] = useState([]);
  const [genre, setGenre] = useState([]);
  const [tag, setTag] = useState([]);
  const [readDate, setReadDate] = useState(null);
  const [selectedItem, setSelectedItem] = useState(null);
  const [marks, setMarks] = useState([]);
  const [alert, setAlert] = useState({ show: false, text: "", variant: "success" });

  // Inline стили
  const styles = {
    container: {
      marginTop: "40px",
    },
    bookImage: {
      width: "100%",
      height: "auto",
      borderRadius: "10px",
      boxShadow: "0 4px 8px rgba(0, 0, 0, 0.1)",
    },
    card: {
      marginTop: "20px",
      padding: "20px",
      borderRadius: "15px",
      boxShadow: "0 4px 8px rgba(0, 0, 0, 0.1)",
    },
    title: {
      fontSize: "32px",
      fontWeight: "bold",
      marginBottom: "10px",
    },
    subtitle: {
      fontSize: "18px",
      fontWeight: "600",
      marginBottom: "20px",
      color: "#555",
    },
    label: {
      fontWeight: "bold",
      color: "#333",
      marginRight: "10px",
    },
    value: {
      color: "#007bff",
    },
    button: {
      marginBottom: "10px",
    },
    listGroup: {
      borderRadius: "10px",
      marginTop: "10px",
    },
    alert: {
      marginBottom: "20px",
    },
  };

  // Загрузка данных о книге
  useEffect(() => {
    const loadBookData = async () => {
      try {
        currentBook.setid(id);

        // Загружаем данные о книге
        const bookData = await fetchOneBook(id);
        currentBook.setBook(bookData);

        const authors = await getBookAuthor(id);
        const genres = await getBookIDGenre(id);
        const tags = await getBookIDTag(id);
        const avgRating = await getBookAvarageRaiting(id);

        setAuthor(authors);
        setGenre(genres);
        setTag(tags);
        setRaiting(avgRating._avg.RATING || 0);

        // Загружаем закладки, если пользователь авторизован
        if (user.isAuth) {
          const bookmarkData = await getBoomarkId(localStorage.getItem("id"), id);
          const bookmarkTypes = [
            { id: 1, name: "Читаю" },
            { id: 2, name: "Прочитано" },
            { id: 3, name: "Хочу прочитать" },
            { id: 4, name: "Брошено" },
            { id: 5, name: "Отложено" },
            { id: 6, name: "Любимое" },
          ];
          setMarks(bookmarkTypes);

          if (bookmarkData) {
            setReadDate(bookmarkData.DATA_READING);
            const selected = bookmarkTypes.find((item) => item.name === bookmarkData.STATUS_READING);
            setSelectedItem(selected || null);
            localStorage.setItem("bookProgress", bookmarkData.MARKS);
          }
        }

        setLoading(false);
      } catch (error) {
        setAlert({ show: true, text: `Ошибка: ${error.message}`, variant: "danger" });
      }
    };

    loadBookData();
  }, [id, user.isAuth, currentBook]);

  const handleDownload = () => {
    const url = `process.env.REACT_APP_API_URL + 'Book' + id + '.EPUB'`;
    console.log(url);
    //window.open(process.env.REACT_APP_API_URL + 'Book' + id + '.EPUB');
    window.open(url);
  };

  const handleBookmarkSelect = async (item) => {
    setSelectedItem(item);
    try {
      await addMarks(localStorage.getItem("id"), id, localStorage.getItem("bookProgress"), item.name);
    } catch (error) {
      setAlert({ show: true, text: `Ошибка при добавлении закладки: ${error.message}`, variant: "danger" });
    }
  };

  if (loading) {
    return <div>Загрузка...</div>;
  }

  return (
    <Container style={styles.container}>
      {alert.show && (
        <Alert variant={alert.variant} style={styles.alert} onClose={() => setAlert({ ...alert, show: false })} dismissible>
          {alert.text}
        </Alert>
      )}
      <Row>
        {/* Левая часть: Обложка книги и действия */}
        <Col xs={12} md={4}>
          <Image
            src={`${process.env.REACT_APP_API_URL}Cover${id}.jpg`}
            style={styles.bookImage}
            fluid
          />
          <Card className="text-center" style={styles.card}>
            <Card.Body>
              {user.isAuth && (
                <>
                  <Button variant="primary" className="w-100" style={styles.button} onClick={handleDownload}>
                    Скачать файл
                  </Button>
                  <ListGroup style={styles.listGroup}>
                    {marks.map((mark) => (
                      <ListGroup.Item
                        key={mark.id}
                        active={selectedItem?.id === mark.id}
                        onClick={() => handleBookmarkSelect(mark)}
                        style={{ cursor: "pointer" }}
                      >
                        {mark.name}
                      </ListGroup.Item>
                    ))}
                  </ListGroup>
                </>
              )}
            </Card.Body>
            <Card.Footer>
              <small className="text-muted">
                {readDate ? `Последнее посещение: ${formatDate(readDate)}` : "Вы здесь впервые"}
              </small>
            </Card.Footer>
          </Card>
        </Col>

        {/* Правая часть: Информация о книге */}
        <Col xs={12} md={8}>
          <Card style={styles.card}>
            <Card.Body>
              <div className="d-flex align-items-center mb-3">
                <img src={`${process.env.REACT_APP_API_URL}star_icon.png`} alt="Рейтинг" width={30} height={30} />
                <h2 className="text-warning ml-2 mb-0">{raiting}</h2>
              </div>
              <h2 style={styles.title}>{currentBook.name}</h2>
              <p style={styles.subtitle}>{currentBook.description}</p>
            </Card.Body>
            <Card.Footer>
              <Row>
                <Col md={4}><span style={styles.label}>Автор:</span></Col>
                <Col md={8}>
                  {author.length > 0 ? (
                    author.map((item, index) => (
                      <Nav.Link key={index} href={`/author/${item.AUTHOR_NAME}/${item.ID}`} style={styles.value}>
                        {item.AUTHOR_NAME}
                      </Nav.Link>
                    ))
                  ) : (
                    <span>Нет информации</span>
                  )}
                </Col>
              </Row>
              <Row>
                <Col md={4}><span style={styles.label}>Жанры:</span></Col>
                <Col md={8}>
                  {genre.length > 0 ? (
                    genre.map((item, index) => (
                      <Nav.Link key={index} href={`/genre/${item.GENRE_NAME}/${item.ID}`} style={styles.value}>
                        {item.GENRE_NAME}
                      </Nav.Link>
                    ))
                  ) : (
                    <span>Нет информации</span>
                  )}
                </Col>
              </Row>
              <Row>
                <Col md={4}><span style={styles.label}>Теги:</span></Col>
                <Col md={8}>
                  {tag.length > 0 ? (
                    tag.map((item, index) => (
                      <Nav.Link key={index} href={`/tag/${item.TAG_NAME}/${item.ID}`} style={styles.value}>
                        {item.TAG_NAME}
                      </Nav.Link>
                    ))
                  ) : (
                    <span>Нет информации</span>
                  )}
                </Col>
              </Row>
              <Row>
                <Col md={4}><span style={styles.label}>Год издания:</span></Col>
                <Col md={8}>
                  {currentBook.year || <span>Нет информации</span>}
                </Col>
              </Row>
              <Row>
                <Col md={4}><span style={styles.label}>Серия книг:</span></Col>
                <Col md={8}>
                  {currentBook.series || <span>Нет информации</span>}
                </Col>
              </Row>
            </Card.Footer>
          </Card>
        </Col>
      </Row>

      {/* Блоки для чтения и отзывов */}
      <Row className="mt-5">
        <Col>
          <ReadBook data={id} />
        </Col>
      </Row>
      <Row className="mt-4">
        <Col>
          <Feedback idBook={id} />
        </Col>
      </Row>
    </Container>
  );
});

export default BookPage;
