import { observer } from "mobx-react-lite";
import React, { useState, useEffect } from "react";
import { Tabs, Tab, Pagination, Row } from "react-bootstrap";
import { getBookmarks } from "../http/userAPI";
import BookItem from "./BookItem";
import BooksList from "./BooksList";
import { useContext } from "react";
import { Context } from "../index";
import { Alert } from "react-bootstrap";


const BookMarks = observer(({ id }) => {
    const { book } = useContext(Context);
    const [key, setKey] = useState(() => {
        const storedKey = localStorage.getItem("myKey");
        return storedKey !== null ? storedKey : "Читаю";
    });
    console.log(key);
    const [page, setPage] = useState(1);
    const [totalPages, setTotalPages] = useState(0);
    const [marks, setMarks] = useState([]);
    const [loading, setLoading] = useState(false);

    let [alertshow, setAlertshow] = React.useState(false);
    const [variant, setVariant] = React.useState('success');
    const [alertText, setAlertText] = React.useState('Успешно');


    useEffect(() => {
        localStorage.setItem("myKey", key);
        const load = async () => {
            console.log(key);
            try {
                setLoading(true);
                const data = await getBookmarks(id, key, page);
                setMarks(data.marks);
                setTotalPages(data.totalPages);
                console.log(marks);
                book.setBooks(data.marks);
            } catch (error) {
                console.error(error);
                setAlertshow(true);
                setVariant('danger');
                setAlertText('Произошла ошибка: ' + error.response.data.message);

            } finally {
                setLoading(false);
            }
        };
        load();
    }, [key, page]);

    if (loading) {
        return <div>Загрузка...</div>;
    }

    return (
        <div>
            {alertshow && <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>{alertText}</Alert>}
            <Tabs id="controlled-tab-example" activeKey={key} onSelect={(k) => setKey(k)} className="mb-3">
                <Tab eventKey="Читаю" title="Читаю" />
                <Tab eventKey="Прочитано" title="Прочитано" />
                <Tab eventKey="Хочу прочитать" title="Хочу прочитать" />
                <Tab eventKey="Брошено" title="Брошено" />
                <Tab eventKey="Отложено" title="Отложено" />
                <Tab eventKey="Любимое" title="Любимое" />
            </Tabs>
            <Row>
                {marks.map((mark) => (
                    <BookItem key={mark.id} book={mark.book} read_date={mark.data_read} />
                ))}
            </Row>
            <Pagination>
                <Pagination.First
                    disabled={page === 1}
                    onClick={() => setPage(1)}
                />
                <Pagination.Prev
                    disabled={page === 1}
                    onClick={() => setPage(page - 1)}
                />

                {/* Отображение страниц */}
                {Array.from({ length: Math.ceil(totalPages) }).map((_, index) => (
                    <Pagination.Item
                        key={index}
                        active={page === index + 1}
                        onClick={() => setPage(index + 1)}
                    >
                        {index + 1}
                    </Pagination.Item>
                ))}

                <Pagination.Next
                    disabled={page === Math.ceil(totalPages)}
                    onClick={() => setPage(page + 1)}
                />
                <Pagination.Last
                    disabled={page === Math.ceil(totalPages)}
                    onClick={() => setPage(Math.ceil(totalPages))}
                />
            </Pagination>


        </div>
    );
});

export default BookMarks;
