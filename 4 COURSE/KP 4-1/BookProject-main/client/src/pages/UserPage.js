import React, {  useEffect, useState } from 'react';
import { Container, Row, Col,  Button,  Image, Card } from 'react-bootstrap';
import { useParams } from "react-router-dom";
import { observer } from "mobx-react-lite";
import { getUserInfo } from '../http/userAPI';

import BookMarks from '../components/BookMarks';
import UpdateUser from '../components/modals/UpdateUser';
import { Alert } from 'react-bootstrap';
import { formatDate } from '../utils/const';

const UserPage = observer(() => {
    const [loading, setLoading] = useState(true);
    const [user, setUser] = useState([]);
    const { id } = useParams();
    const currentId = localStorage.getItem('id');
    const [show, setShow] = useState(false);

    let [alertshow, setAlertshow] = React.useState(false);
    const [variant, setVariant] = React.useState('success');
    const [alertText, setAlertText] = React.useState('Книга успешно изменена');



    useEffect(() => {
        const load = async () => {
            try {
                await getUserInfo(id).then(data => {
                    setUser(data);
                });
            } catch (e) {
                setAlertshow(true);
                setVariant('danger');
                setAlertText('Произошла ошибка: ' + e.response.data.message);

            }
        }
        load();
        setLoading(false);
    }, [id, user.USER_NAME, user.USER_INFO]);

    if (loading) {
        return <div>Загрузка...</div>;
    }

    return (
        <Container>
            {alertshow && <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>{alertText}</Alert>}

            <Row className="d-flex justify-content-center mt-5">
                <Col md={6}>
                    <h3 className="text-center">Личный кабинет</h3>
                </Col>
            </Row>
            <Row>
                <Col md={4}>
                    <Image src={process.env.REACT_APP_API_URL + 'User' + id + '.jpg'} style={{ width: '200px', height: '200px', objectFit: 'cover' }} className="m-2" />
                    {id == currentId &&
                        <Button variant="outline-primary" onClick={() => setShow(true)} className="m-2">Редактировать профиль</Button>
                    }
                </Col >
                <Col md={6}>
                    <Card >
                        <Card.Body>
                            <Card.Title>{user.USER_NAME}</Card.Title>
                            <Card.Body>
                                {user.USER_INFO}
                            </Card.Body>
                            <Card.Footer>
                                <small className="text-muted">Дата регистрации: {formatDate(user.DATA_CREATE)}</small>
                            </Card.Footer>
                        </Card.Body>
                    </Card>
                </Col>
            </Row>
            {id == currentId &&
                <Row>
                    <Col md={10}>
                        <BookMarks id={id} />
                    </Col>
                </Row>}
            <UpdateUser show={show} onHide={() => setShow(false)} user={user} />

        </Container>
    );
});

export default UserPage;