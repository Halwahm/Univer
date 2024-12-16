import React, { useState, useEffect } from 'react';
import Select from 'react-select';
import { Form, Row, Col } from 'react-bootstrap';
import { fetchBookFilter, fetchTags, fetchAuthor, fetchGanre } from '../http/bookAPI';
import BookItem from './BookItem';
import { Pagination } from 'react-bootstrap';

const BookList = () => {
    const [books, setBooks] = useState([]);
    const [totalPages, setTotalPages] = useState(1);
    const [currentPage, setCurrentPage] = useState(1);
    const [genres, setGenres] = useState([]);
    const [tags, setTags] = useState([]);
    const [authors, setAuthors] = useState([]);
    const [searchTerm, setSearchTerm] = useState('');
    const [filterParams, setFilterParams] = useState({ tags: [], genres: [], authors: [] });

    // Получение фильтров с сервера
    useEffect(() => {
        async function fetchFilters() {
            try {
                const _genres = await fetchGanre(0);
                setGenres(_genres.map((genre) => ({ value: genre.ID, label: genre.GENRE_NAME })));
                const _tags = await fetchTags(0);
                setTags(_tags.map((tag) => ({ value: tag.ID, label: tag.TAG_NAME })));
                const _authors = await fetchAuthor(0);
                setAuthors(_authors.map((author) => ({ value: author.ID, label: author.AUTHOR_NAME })));
            } catch (error) {
                console.error('Ошибка при загрузке фильтров:', error);
            }
        }

        fetchFilters();
    }, []);

    // Получение данных книг
    useEffect(() => {
        async function fetchData() {
            try {
                const result = await fetchBookFilter(currentPage, searchTerm, filterParams);
                setBooks(result.books);
                setTotalPages(result.totalPages);
            } catch (error) {
                console.error('Ошибка при загрузке книг:', error);
            }
        }

        fetchData();
    }, [currentPage, searchTerm, filterParams]);

    const handleChange = (type, selectedOptions) => {
        setFilterParams({ ...filterParams, [type]: selectedOptions });
        setCurrentPage(1); // Сбрасываем на первую страницу
    };

    const handleSearchChange = (e) => {
        setSearchTerm(e.target.value);
        setCurrentPage(1); // Сбрасываем на первую страницу
    };

    return (
        <div>
            <Form className="w-100">
                <Row>
                    <Form.Group controlId="searchTerm" className="w-100 mb-3">
                        <Form.Label>Поиск</Form.Label>
                        <Form.Control
                            type="text"
                            placeholder="Введите название книги, серию или год издания..."
                            value={searchTerm}
                            onChange={handleSearchChange}
                        />
                    </Form.Group>
                </Row>
                <Row>
                    <Col xs={12} md={4}>
                        <Form.Group controlId="authors" className="w-100">
                            <Form.Label>Авторы</Form.Label>
                            <Select
                                options={authors}
                                isMulti
                                placeholder="Выберите авторов..."
                                value={filterParams.authors}
                                onChange={(selectedOptions) => handleChange('authors', selectedOptions)}
                            />
                        </Form.Group>
                    </Col>
                    <Col xs={12} md={4}>
                        <Form.Group controlId="genres" className="w-100">
                            <Form.Label>Жанры</Form.Label>
                            <Select
                                options={genres}
                                isMulti
                                placeholder="Выберите жанры..."
                                value={filterParams.genres}
                                onChange={(selectedOptions) => handleChange('genres', selectedOptions)}
                            />
                        </Form.Group>
                    </Col>
                    <Col xs={12} md={4}>
                        <Form.Group controlId="tags" className="w-100">
                            <Form.Label>Теги</Form.Label>
                            <Select
                                options={tags}
                                isMulti
                                placeholder="Выберите теги..."
                                value={filterParams.tags}
                                onChange={(selectedOptions) => handleChange('tags', selectedOptions)}
                            />
                        </Form.Group>
                    </Col>
                </Row>
            </Form>

            <div className="d-flex justify-content-center align-items-center mt-4">
                <div style={{ display: 'flex', flexWrap: 'wrap', gap: '10px' }}>
                    {books.map((book) => (
                        <BookItem key={book.ID} book={book} />
                    ))}
                </div>
            </div>

            <Pagination>
                <Pagination.First
                    disabled={currentPage === 1}
                    onClick={() => setCurrentPage(1)}
                />
                <Pagination.Prev
                    disabled={currentPage === 1}
                    onClick={() => setCurrentPage(currentPage - 1)}
                />
                {Array.from({ length: totalPages }).map((_, index) => (
                    <Pagination.Item
                        key={index}
                        active={currentPage === index + 1}
                        onClick={() => setCurrentPage(index + 1)}
                    >
                        {index + 1}
                    </Pagination.Item>
                ))}
                <Pagination.Next
                    disabled={currentPage === totalPages}
                    onClick={() => setCurrentPage(currentPage + 1)}
                />
                <Pagination.Last
                    disabled={currentPage === totalPages}
                    onClick={() => setCurrentPage(totalPages)}
                />
            </Pagination>
        </div>
    );
};

export default BookList;
