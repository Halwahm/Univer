import React, { useState, useEffect } from "react";
import { Button, Modal, Form, Alert } from "react-bootstrap";
import Select from "react-select";
import { editBook, uploadFile, fetchGanre, fetchTags } from "../../http/bookAPI";

const EditBook = ({ show, onHide, bookData = {}, onEditComplete }) => {
    const [file, setFile] = useState(null); 
    const [fimg, setFimg] = useState(null);
    const [name, setName] = useState("");
    const [info, setInfo] = useState("");
    const [series, setSeries] = useState("");
    const [year, setYear] = useState("");
    const [chapters, setChapters] = useState("");
    const [genres, setGenres] = useState([]);
    const [tags, setTags] = useState([]);
    const [selectedGenre, setSelectedGenre] = useState([]);
    const [selectedTag, setSelectedTag] = useState([]);    

    const [alertShow, setAlertShow] = useState(false);
    const [variant, setVariant] = useState("success");
    const [alertText, setAlertText] = useState("");
    const [isFormValid, setIsFormValid] = useState(false);

    useEffect(() => {
        const loadGenresAndTags = async () => {
            try {
                const genresData = await fetchGanre(0);
                setGenres(genresData || []); // Гарантируем, что это массив
    
                const tagsData = await fetchTags(0);
                setTags(tagsData || []); // Гарантируем, что это массив
            } catch (error) {
                console.error("Ошибка при загрузке жанров и тегов:", error);
            }
        };
    
        loadGenresAndTags();
    }, []);    

    useEffect(() => {
        if (bookData && bookData.ID) {
            setName(bookData.BOOK_NAME || "");
            setInfo(bookData.BOOK_DESCRIPTION || "");
            setSeries(bookData.BOOK_SERIES || "");
            setYear(bookData.DATA_RELEASE || "");
            setChapters(bookData.CHAPTERS || "");
            setSelectedGenre(
                Array.isArray(bookData.GENRES)
                    ? bookData.GENRES.map((genre) => genre.ID)
                    : []
            );
            setSelectedTag(
                Array.isArray(bookData.TAGS)
                    ? bookData.TAGS.map((tag) => tag.ID)
                    : []
            );
        }
    }, [bookData]);

    useEffect(() => {
        setIsFormValid(
            name.trim() !== "" &&
            info.trim() !== "" &&
            series.trim() !== "" &&
            !isNaN(year) &&
            year !== "" &&
            !isNaN(chapters) &&
            chapters.toString().trim() !== "" &&
            selectedGenre.length > 0 &&
            selectedTag.length > 0
        );
    }, [name, info, series, year, chapters, selectedGenre, selectedTag]);
    

    const handleFileSelect = (e) => setFile(e.target.files[0]);
    const handleImageSelect = (e) => setFimg(e.target.files[0]);

    const handleEdit = async () => {
        if (!isFormValid) {
            setAlertText("Пожалуйста, заполните все поля корректно.");
            setVariant("danger");
            setAlertShow(true);
            return;
        }

        const updatedBook = {
            BOOK_NAME: name,
            BOOK_DESCRIPTION: info,
            BOOK_SERIES: series,
            DATA_RELEASE: year ? parseInt(year, 10) : null,
            CHAPTERS: parseInt(chapters),
            GENRES: selectedGenre,
            TAGS: selectedTag,
        };

        try {
            // Отправка обновленных данных книги
            const result = await editBook(parseInt(bookData.ID), updatedBook);

            // Загрузка файла книги
            if (file && file.type === "application/epub+zip") {
                const formData = new FormData();
                formData.append("file", file);
                formData.append("name", `Book${result.ID}.epub`);
                await uploadFile(formData);
            }

            // Загрузка обложки книги
            if (fimg && fimg.type === "image/jpeg") {
                const formData = new FormData();
                formData.append("file", fimg);
                formData.append("name", `Cover${result.ID}.jpg`);
                await uploadFile(formData);
            }

            // Успешное обновление
            setAlertText("Книга успешно обновлена!");
            setVariant("success");
            setAlertShow(true);

            // Закрываем модальное окно и обновляем список
            setTimeout(() => {
                setAlertShow(false);
                onHide();
                if (onEditComplete) onEditComplete();
            }, 1500);
        } catch (error) {
            setAlertText("Ошибка при обновлении книги.");
            setVariant("danger");
            setAlertShow(true);
            console.error("Ошибка при обновлении книги:", error);
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
                <Modal.Title>Редактировать книгу</Modal.Title>
            </Modal.Header>
            <Modal.Body>
                <Form>
                    <Form.Group controlId="formFile" className="mb-3">
                        <Form.Label>Изменить файл книги</Form.Label>
                        <Form.Control type="file" onChange={handleFileSelect} />
                    </Form.Group>
                    <Form.Group controlId="formFileImg" className="mb-3">
                        <Form.Label>Изменить обложку книги</Form.Label>
                        <Form.Control type="file" onChange={handleImageSelect} />
                    </Form.Group>
                    <Form.Control
                        value={name}
                        onChange={(e) => setName(e.target.value)}
                        className="mt-3"
                        placeholder="Название книги"
                    />
                    <Form.Control
                        value={info}
                        onChange={(e) => setInfo(e.target.value)}
                        className="mt-3"
                        placeholder="Описание книги"
                    />
                    <Form.Control
                        value={series}
                        onChange={(e) => setSeries(e.target.value)}
                        className="mt-3"
                        placeholder="Серия книги"
                    />
                    <Form.Control
                        value={year}
                        onChange={(e) => setYear(e.target.value)}
                        className="mt-3"
                        placeholder="Год выпуска"
                    />
                    <Form.Control
                        value={chapters}
                        onChange={(e) => setChapters(e.target.value)}
                        className="mt-3"
                        placeholder="Количество глав"
                    />
                    <Form.Group className="mb-3">
                        <Form.Label>Выберите жанры:</Form.Label>
                        <Select
                            isMulti
                            options={(genres || []).map((genre) => ({
                                value: genre.ID,
                                label: genre.GENRE_NAME,
                            }))}
                            value={Array.isArray(selectedGenre) ? selectedGenre.map((genre) => ({
                                value: genre,
                                label: (genres || []).find((g) => g.ID === genre)?.GENRE_NAME,
                            })) : []}
                            onChange={(selected) => setSelectedGenre(selected.map((option) => option.value))}
                        />
                    </Form.Group>

                    <Form.Group className="mb-3">
                        <Form.Label>Выберите теги:</Form.Label>
                        <Select
                            isMulti
                            options={(tags || []).map((tag) => ({
                                value: tag.ID,
                                label: tag.TAG_NAME,
                            }))}
                            value={Array.isArray(selectedTag) ? selectedTag.map((tag) => ({
                                value: tag,
                                label: (tags || []).find((t) => t.ID === tag)?.TAG_NAME,
                            })) : []}
                            onChange={(selected) => setSelectedTag(selected.map((option) => option.value))}
                        />
                    </Form.Group>
                    <Button
                        variant="outline-success"
                        className="mt-3"
                        onClick={handleEdit}
                        disabled={!isFormValid}
                    >
                        Сохранить изменения
                    </Button>
                </Form>
            </Modal.Body>
        </Modal>
    );
};

export default EditBook;
