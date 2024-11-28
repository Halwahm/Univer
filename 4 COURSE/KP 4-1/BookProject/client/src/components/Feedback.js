import React, { useEffect, useState, useContext } from 'react';
import { Container, Row, Col, Form, Button, ListGroup } from 'react-bootstrap';
import { Context } from '../index';
import { observer } from "mobx-react-lite";
import { getComments } from "../http/bookAPI";
import { getAuth, getUserInfo } from '../http/userAPI';
import { io } from 'socket.io-client';
import ItemFeed from './ItemFeed';
import { Alert } from 'react-bootstrap';



const Feedback = observer(({ idBook }) => {
    const { user } = useContext(Context)
    const [feedback, setFeedback] = useState([]);
    const [messages, setMessages] = useState([]);
    const [inputValue, setInputValue] = useState('');
    const [raiting, setRaiting] = useState(0);
    const socket = io(process.env.REACT_APP_API_URL);

    let [alertshow, setAlertshow] = React.useState(false);
    const [variant, setVariant] = React.useState('success');
    const [alertText, setAlertText] = React.useState('Успешно');


    useEffect(() => {
        const load = async () => {
            try {
                console.log(idBook);
                const response = await getComments(idBook, 1)
                console.log(response)
                setFeedback(response)
                const user_id = localStorage.getItem('id');
                if (user_id) 
                await getUserInfo(user_id).then(data => {
                    user.setUser(data);
                }).catch(e => {
                    setAlertshow(true);
                    setVariant('danger');
                    setAlertText('Произошла ошибка: ' + e.response.data.message);
                });
            } catch (e) {
                setAlertshow(true);
                setVariant('danger');
                setAlertText('Произошла ошибка: ' + e.response.data.message);
            }
        }
        load();
    }, [idBook]);

    useEffect(() => {
        try {
            socket.on('message', (msg) => {
                console.log(msg);
                setMessages([...messages, msg]);
                console.log(messages);
            });
        } catch (e) {
            setAlertshow(true);
            setVariant('danger');
            setAlertText('Произошла ошибка: ' + e.response.data.message);
        }
    }, [messages]);

    const handleSend = (event) => {
        event.preventDefault();
        if (inputValue.trim() === '' || raiting < 0 || raiting > 10) {
            setAlertshow(true);
            setVariant('danger');
            setAlertText('Пожалуйста, введите отзыв и укажите корректную оценку (0-10).');
            return;
        }
        setAlertshow(false);
        const message = {
            id: user.user.ID,
            id_Book: idBook,
            text: inputValue,
            raiting: raiting
        };
        try {
            socket.emit('message', message);
        }
        catch (e) {
            setAlertshow(true);
            setVariant('danger');
            setAlertText('Произошла ошибка: ' + e.response.data.message);
        }
        setInputValue('');
    };
    return (
        <Container className="mt-10">
            {alertshow && <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>{alertText}</Alert>}
        {user.isAuth && <h3>Оставить отзыв</h3>}
        {user.isAuth && 
            <Form onSubmit={handleSend}>
                <Form.Label>Отзыв</Form.Label>
                <Form.Control
                    type="text"
                    value={inputValue}
                    onChange={(event) => setInputValue(event.target.value)}
                    placeholder="Введите отзыв"
                />
                <Form.Label>Оценка</Form.Label>
                <Form.Control
                    type="number"
                    value={raiting}
                    onChange={(event) => setRaiting(event.target.value)}
                    placeholder="Введите оценку"
                />
                <Button type="submit">Отправить</Button>
            </Form>
}
            <hr />
            <div>
                <ListGroup>
                    <ListGroup.Item>Отзывы</ListGroup.Item>
                </ListGroup>
                {messages.map((msg) => (
                    <ItemFeed key={msg.ID} data={msg} />
                ))}
                {feedback.map((msg) => (
                    <ItemFeed key={msg.ID} data={msg} />
                ))}
            </div>

        </Container>
    );
});

export default Feedback;
