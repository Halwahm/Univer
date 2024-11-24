import { observer } from "mobx-react-lite";
import React, { useContext } from "react";
import { fetchOneBook, getBookIDGenre } from "../http/bookAPI";

import { Container, Row, Form, Table, Button, Alert, Col, Badge, CloseButton } from "react-bootstrap";
import { Context } from "../index";
import { useEffect } from "react";
import { uploadFile, editBook, fetchFile, fetchGanre, fetchTags, addBookIDGenre, delBookIDGenre, delBookIDTag, addBookIDTag, getBookIDTag, fetchAuthor, delBookAuthor, addBookAuthor, getBookAuthor } from "../http/bookAPI";
import { Typeahead } from 'react-bootstrap-typeahead';
import { useNavigate } from "react-router-dom";


const AdminBook = observer(() => {
    let { currentBook } = useContext(Context)
    let [files, setFiles] = React.useState(null);
    let [fimg, setFimg] = React.useState(null);
    let [name, setName] = React.useState("");
    let [info, setInfo] = React.useState("");
    let [series, setSeries] = React.useState("");
    let [year, setYear] = React.useState("");
    let [chapters, setChapters] = React.useState("");
    const id = localStorage.getItem('bookId');
    //Вывод alert
    let [alertshow, setAlertshow] = React.useState(false);
    const [variant, setVariant] = React.useState('success');
    const [alertText, setAlertText] = React.useState('Книга успешно изменена');

    const [allGanre, setAllGanre] = React.useState([]);
    const [selectedGanre, setSelectedGanre] = React.useState([]);
    //Ganre
    let [ganre, setGanre] = React.useState([]);
    //+
    const delGenre = async (genre) => {
        console.log(genre);
        const data = await delBookIDGenre(id, genre);
        const datagenre = await getBookIDGenre(id);
        setGanre(datagenre);
    }
    //+
    const addGanre = async () => {
        console.log(selectedGanre);
        const data = await addBookIDGenre(id, selectedGanre);
        const datagenre = await getBookIDGenre(id);
        setGanre(datagenre);
        setSelectedGanre([]);
    }

    const [allTag, setAllTag] = React.useState([]);
    const [selectedTag, setSelectedTag] = React.useState([]);
    //Tag
    let [tag, setTag] = React.useState([]);
    const delTag = async (tag) => {
        console.log(tag);
        const data = await delBookIDTag(id, tag);
        const datatag = await getBookIDTag(id);
        setTag(datatag);
    }
    const addTag = async () => {
        console.log(selectedTag);
        const data = await addBookIDTag(id, selectedTag);
        const datatag = await getBookIDTag(id);
        setTag(datatag);
        setSelectedTag([]);
    }
    //Autor
    let [author, setAuthor] = React.useState([]);
    let [allAuthor, setAllAuthor] = React.useState([]);
    let [selectedAuthor, setSelectedAuthor] = React.useState([]);
    const delAuthor = async (author) => {
        console.log(author);
        const data = await delBookAuthor(id, author);
        const dataautor = await getBookAuthor(id);
        setAuthor(dataautor);
    }
    const addAuthor = async () => {
        console.log(selectedAuthor);
        const data = await addBookAuthor(id, selectedAuthor);
        const dataautor = await getBookAuthor(id);
        setAuthor(dataautor);
        setSelectedAuthor([]);
    }


    try {
        useEffect(() => {
            currentBook.setid(id);
            async function fetchData() {
                const data = await fetchOneBook(id);
                currentBook.setBook(data);
                const datagenre = await getBookIDGenre(id);
                setGanre(datagenre);
                const datatag = await getBookIDTag(id);
                setTag(datatag);
                const dataautor = await getBookAuthor(id);
                console.log(dataautor);
                setAuthor(dataautor);
                const dataGanre = await fetchGanre(0);
                setAllGanre(dataGanre);
                const dataTag = await fetchTags(0);
                setAllTag(dataTag);
                const dataAutor = await fetchAuthor(0);
                setAllAuthor(dataAutor);
                console.log(author);

                console.log(allGanre);
                console.log(currentBook);
                setName(currentBook.name);
                setInfo(currentBook.description);
                setSeries(currentBook.series);
                setYear(currentBook.year);
                setChapters(currentBook.chapters);
            }
            fetchData();
            //console.log(data);

        }, [currentBook]);
    } catch (e) {
        setAlertshow(true);
        setVariant('fail');
        setAlertText('Произошла ошибка:' + e.message);
    }

    const Edit = async () => {
        const newbook = {
            BOOK_NAME: name,
            BOOK_INFO: info,
            BOOK_SERIES: series,
            BOOK_RELEASE: year,
            CHAPTERS: chapters
        };
        console.log(newbook);
        try {
            const result = await editBook(id, newbook);
            console.log(result);
            console.log(files);
            console.log(fimg);
            if (files != null) {
                const formData = new FormData();
                formData.append('file', files);
                formData.append('name', 'Book' + result.ID + '.epub');
                const data = await uploadFile(formData);
            }
            if (fimg != null) {
                const formData = new FormData();
                formData.append('file', fimg);
                console.log(fimg);
                formData.append('name', 'Cover' + result.ID + '.jpg');
                const data = await uploadFile(formData);
            }
            //await uploadFile(img, 'Cover' + result.ID + '.jpg');
        } catch (error) {
            console.log(error);
            setAlertshow(true);
            setVariant('danger');
            setAlertText('Произошла ошибка:' + error.message);
        } finally {
            setAlertshow(true);
            setVariant('success');
            setAlertText('Книга успешно изменена');
        }
        //
    }
    const navigate = useNavigate();
    const Back = () => {
        navigate(-1);
    }


    return (
        <Container>
            {alertshow && <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>{alertText}</Alert>}
            <Row className="d-flex">
                <Form>
                    <Form.Group controlId="formFile" className="mb-3">
                        <Form.Label>Изменить файл книги</Form.Label>
                        <Form.Control
                            type="file"
                            onChange={(event) => {
                                const file = event.target.files[0];
                                setFiles(file);
                            }}
                            accept=".epub"
                        />
                    </Form.Group>
                    <Form.Group controlId="formFile" className="mb-3">
                        <Form.Label>Изменить обложку книги</Form.Label>
                        <Form.Control
                            type="file"
                            onChange={(event) => {
                                const file = event.target.files[0];
                                setFimg(file);
                            }}
                        />
                    </Form.Group>
                    <Form.Control
                        value={name}
                        onChange={e => setName(e.target.value)}
                        className="mt-3"
                        placeholder="Введите название книги"
                    />
                    <Form.Control
                        value={info}
                        onChange={e => setInfo(e.target.value)}
                        className="mt-3"
                        placeholder="Введите описание книги"
                    />
                    <Form.Control
                        value={series}
                        onChange={e => setSeries(e.target.value)}
                        className="mt-3"
                        placeholder="Введите серию книги"
                    />
                    <Form.Control
                        value={year}
                        onChange={e => setYear(e.target.value)}
                        className="mt-3"
                        placeholder="Введите год выпуска книги"
                    />
                    <Form.Control
                        value={chapters}
                        onChange={e => setChapters(e.target.value)}
                        className="mt-3"
                        placeholder="Введите количество глав книги"
                    />
                    <Row className="d-flex">
                        <div>
                            {ganre.map((ganr) =>
                                <Badge bg="primary" key={ganr.ID} className="mt-3 me-1" >
                                    {ganr.GENRE_NAME}
                                    <CloseButton className="ms-2" onClick={() => delGenre(ganr.ID)} />
                                </Badge>
                            )}
                        </div>
                        <Row className="d-flex align-items-center ml-3">
                            <Col className="pl-10 pt-0 mt-0">
                                <Typeahead
                                    className="mt-0 mb-0"
                                    id="my-typeahead"
                                    labelKey="GENRE_NAME"
                                    options={allGanre}
                                    selectHintOnEnter={true}
                                    selected={selectedGanre}
                                    onChange={setSelectedGanre}
                                    placeholder="Выбирите жанр книги"
                                />
                            </Col>
                            <Col className="p-0">
                                <Button variant="outline-success" className="d-flex mt-0 mb-0" onClick={addGanre}>
                                    Добавить жанр
                                </Button>
                            </Col>
                        </Row>
                    </Row>
                    <Row className="d-flex">
                        <div>
                            {tag.map((tag) =>
                                <Badge bg="primary" key={tag.ID} className="mt-3 me-1" >
                                    {tag.TAG_NAME}
                                    <CloseButton className="ms-2" onClick={() => delTag(tag.ID)} />
                                </Badge>
                            )}
                        </div>
                        <Row className="d-flex align-items-center ml-3">
                            <Col className="pl-10 pt-0 mt-0">
                                <Typeahead
                                    className="mt-0 mb-0"
                                    id="my-typeahead"
                                    labelKey="TAG_NAME"
                                    options={allTag}
                                    selectHintOnEnter={true}
                                    selected={selectedTag}
                                    onChange={setSelectedTag}
                                    placeholder="Выбирите тег книги"
                                />
                            </Col>
                            <Col className="p-0">
                                <Button variant="outline-success" className="d-flex mt-0 mb-0" onClick={addTag}>
                                    Добавить тег
                                </Button>
                            </Col>
                        </Row>
                    </Row>
                    <Row className="d-flex">
                        <div>
                            {author.map((aut) =>
                                <Badge bg="primary" key={aut.ID} className="mt-3 me-1" >
                                    {aut.AUTHOR_NAME}
                                    <CloseButton className="ms-2" onClick={() => delAuthor(aut.ID)} />
                                </Badge>
                            )}
                        </div>
                        <Row className="d-flex align-items-center ml-3">
                            <Col className="pl-10 pt-0 mt-0">
                                <Typeahead
                                    className="mt-0 mb-0"
                                    id="my-typeahead"
                                    labelKey="AUTHOR_NAME"
                                    options={allAuthor}
                                    selectHintOnEnter={true}
                                    selected={selectedAuthor}
                                    onChange={setSelectedAuthor}
                                    placeholder="Выбирите автора книги"
                                />
                            </Col>
                            <Col className="p-0">
                                <Button variant="outline-success" className="d-flex mt-0 mb-0" onClick={addAuthor}>
                                    Добавить автора
                                </Button>
                            </Col>
                        </Row>
                    </Row>

                    <Button variant="outline-success" className="mt-3" onClick={Edit}>Изменить</Button>
                    <Button variant="outline-secondary" className="mt-3 ms-3" onClick={Back}>Назад</Button>
                </Form>

            </Row>

        </Container>
    );
}
);

export default AdminBook;