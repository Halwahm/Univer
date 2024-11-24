import React, { useState, useEffect } from "react";
import { Button, Modal, Form, Alert } from "react-bootstrap";
import { createBook, uploadFile, fetchGanre, fetchTags } from "../../http/bookAPI";

const CreateBook = ({ show, onHide }) => {
    const [file, setFile] = useState(null);
    const [fimg, setFimg] = useState(null);
    const [name, setName] = useState("");
    const [info, setInfo] = useState("");
    const [series, setSeries] = useState("");
    const [year, setYear] = useState("");
    const [chapters, setChapters] = useState("");
    const [genres, setGenres] = useState([]);
    const [tags, setTags] = useState([]);
    const [selectedGenre, setSelectedGenre] = useState("");
    const [selectedTag, setSelectedTag] = useState("");
    const [isFormValid, setIsFormValid] = useState(false);

    const [alertShow, setAlertShow] = useState(false);
    const [variant, setVariant] = useState("success");
    const [alertText, setAlertText] = useState("");

    useEffect(() => {
        const loadGenresAndTags = async () => {
            try {
                const genresData = await fetchGanre(0);
                setGenres(genresData || []);

                const tagsData = await fetchTags(0);
                setTags(tagsData || []);
            } catch (error) {
                console.error("Ошибка при загрузке жанров и тегов:", error);
            }
        };

        loadGenresAndTags();
    }, []);

    useEffect(() => {
        setIsFormValid(
            name.trim() !== "" &&
            info.trim() !== "" &&
            series.trim() !== "" &&
            !isNaN(year) &&
            year.trim() !== "" &&
            !isNaN(chapters) &&
            chapters.trim() !== "" &&
            file !== null &&
            file.type === "application/epub+zip" &&
            fimg !== null &&
            fimg.type === "image/jpeg" &&
            selectedGenre !== "" &&
            selectedTag !== ""
        );
    }, [name, info, series, year, chapters, file, fimg, selectedGenre, selectedTag]);

    const addBook = async () => {
        const newBook = {
            BOOK_NAME: name,
            BOOK_DESCRIPTION: info,
            BOOK_SERIES: series,
            DATA_RELEASE: parseInt(year),
            CHAPTERS: parseInt(chapters),
            GENRES: [parseInt(selectedGenre)],
            TAGS: [parseInt(selectedTag)],
        };

        try {
            const result = await createBook(newBook);

            if (file && file.type === "application/epub+zip") {
                const formData = new FormData();
                formData.append("file", file);
                formData.append("name", `Book${result.ID}.epub`);
                await uploadFile(formData);
            }

            if (fimg && fimg.type === "image/jpeg") {
                const formData = new FormData();
                formData.append("file", fimg);
                formData.append("name", `Cover${result.ID}.jpg`);
                await uploadFile(formData);
            }

            setAlertText("Книга успешно добавлена!");
            setVariant("success");
            setAlertShow(true);
            setTimeout(() => {
                setAlertShow(false);
                onHide();
            }, 1500);
        } catch (error) {
            setAlertText("Ошибка при добавлении книги.");
            setVariant("danger");
            setAlertShow(true);
        }
    };

    return (
        <Modal show={show} onHide={onHide} size="lg" centered>
            {alertShow && (
                <Alert variant={variant} className="mt-3" onClose={() => setAlertShow(false)} dismissible>
                    {alertText}
                </Alert>
            )}
            <Modal.Header closeButton>
                <Modal.Title>Добавить книгу</Modal.Title>
            </Modal.Header>
            <Modal.Body>
                <Form>
                    <Form.Group controlId="formFile" className="mb-3">
                        <Form.Label>Загрузить файл книги</Form.Label>
                        <Form.Control type="file" onChange={(e) => setFile(e.target.files[0])} />
                    </Form.Group>
                    <Form.Group controlId="formFileCover" className="mb-3">
                        <Form.Label>Загрузить обложку книги</Form.Label>
                        <Form.Control type="file" onChange={(e) => setFimg(e.target.files[0])} />
                    </Form.Group>
                    <Form.Control
                        value={name}
                        onChange={(e) => setName(e.target.value)}
                        placeholder="Введите название книги"
                        className="mt-3"
                    />
                    <Form.Control
                        value={info}
                        onChange={(e) => setInfo(e.target.value)}
                        placeholder="Введите описание книги"
                        className="mt-3"
                    />
                    <Form.Control
                        value={series}
                        onChange={(e) => setSeries(e.target.value)}
                        placeholder="Введите серию книги"
                        className="mt-3"
                    />
                    <Form.Control
                        value={year}
                        onChange={(e) => setYear(e.target.value)}
                        placeholder="Введите год выпуска книги"
                        className="mt-3"
                    />
                    <Form.Control
                        value={chapters}
                        onChange={(e) => setChapters(e.target.value)}
                        placeholder="Введите количество глав книги"
                        className="mt-3"
                    />
                    <Form.Group className="mb-3">
                        <Form.Label>Выберите жанр:</Form.Label>
                        <Form.Select
                            value={selectedGenre}
                            onChange={(e) => setSelectedGenre(e.target.value)}
                        >
                            <option value="">Выберите жанр</option>
                            {genres.map((genre) => (
                                <option key={genre.ID} value={genre.ID}>
                                    {genre.GENRE_NAME}
                                </option>
                            ))}
                        </Form.Select>
                    </Form.Group>

                    <Form.Group className="mb-3">
                        <Form.Label>Выберите тег:</Form.Label>
                        <Form.Select
                            value={selectedTag}
                            onChange={(e) => setSelectedTag(e.target.value)}
                        >
                            <option value="">Выберите тег</option>
                            {tags.map((tag) => (
                                <option key={tag.ID} value={tag.ID}>
                                    {tag.TAG_NAME}
                                </option>
                            ))}
                        </Form.Select>
                    </Form.Group>

                    <Button
                        variant="outline-success"
                        className="mt-3"
                        onClick={addBook}
                        disabled={!isFormValid}
                    >
                        Добавить
                    </Button>
                </Form>
            </Modal.Body>
        </Modal>
    );
};

export default CreateBook;
