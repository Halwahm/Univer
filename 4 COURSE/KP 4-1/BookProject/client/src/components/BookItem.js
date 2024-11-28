import { observer } from "mobx-react-lite";
import React, { useState } from "react";
import { Card, Col, Image, Row } from "react-bootstrap";
import { useNavigate } from "react-router-dom";
import { BOOK_PAGE_ROUTE } from "../utils/const";
import { useLocation } from "react-router-dom";
import { useEffect } from "react";
import { getBookAvarageRaiting } from "../http/bookAPI";
import { formatDate } from '../utils/const';
import { Alert } from "react-bootstrap";
import { set } from "mobx";


const BookItem = observer(({ book, read_date }) => {
    const history = useNavigate();
    console.log(history);
    console.log(read_date);
    console.log(book.book_author);
    const location = useLocation();
    let [raiting, setRaiting] = useState(0);
    let [author, setAuthor] = useState([]);
    let [genre, setGenre] = useState([]);

    let [alertshow, setAlertshow] = React.useState(false);
    const [variant, setVariant] = React.useState('success');
    const [alertText, setAlertText] = React.useState('Успешно');
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        try{
        getBookAvarageRaiting(book.ID).then(data => {
            console.log(data);
            if (data._avg.RATING == null) {
                setRaiting(0);
            }
            else {
                setRaiting(data._avg.RATING);
            }
            setLoading(false);
        });
    }  catch (e) {
        setAlertshow(true);
        setVariant('danger');
        setAlertText('Произошла ошибка: ' + e.response.data.message);
    }
    })

    if (loading) {
        return <div>Загрузка...</div>;
    }

    return (
        <Row onClick={() => {
            history(BOOK_PAGE_ROUTE + '/' + book.ID)
        }} className="d-flex m-2 p-0">
        {alertshow && <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>{alertText}</Alert>}
            <Card className="p-0" style={{ width: '180px', cursor: 'pointer' }}>
                <Image
                    width={180}
                    height={250}
                    src={process.env.REACT_APP_API_URL + 'Cover' + book.ID + '.jpg'}
                />
                <Card.Body>
                    <div className="d-flex h-230 align-items-center">
                        <img src={process.env.REACT_APP_API_URL + "star_icon.png"} alt="star" width={16} height={16} />
                        <p style={{ color: '#FFA500' }} className="ml-2 mb-0">{raiting}</p>
                    </div>
                    <Card.Title>{book.BOOK_NAME}</Card.Title>
                    <Card.Text style={{ fontSize: '14px' }}>
                        {book.BOOK_SERIES}
                        </Card.Text>

                </Card.Body>
                {read_date && <Card.Footer style={{ fontSize: '14px' }}>Был <i> {formatDate(read_date)}</i></Card.Footer>}
            </Card>
        </Row>

    );
});

export default BookItem;