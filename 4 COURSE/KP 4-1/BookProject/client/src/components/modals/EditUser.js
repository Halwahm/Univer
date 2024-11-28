import React, { useState, useEffect } from "react";
import { Modal, Button, Form, Alert } from "react-bootstrap";
import { editUser } from "../http/userAPI";

const EditUser = ({ show, onHide, userData, onEditComplete }) => {
    const [name, setName] = useState("");
    const [info, setInfo] = useState("");
    const [alertShow, setAlertShow] = useState(false);
    const [variant, setVariant] = useState("success");
    const [alertText, setAlertText] = useState("");

    useEffect(() => {
        if (userData) {
            setName(userData.USER_NAME || "");
            setInfo(userData.USER_INFO || "");
        }
    }, [userData]);

    const handleEdit = async () => {
        try {
            const updatedUser = {
                USER_NAME: name,
                USER_INFO: info,
            };
            await editUser(userData.ID, updatedUser);
            setAlertText("Пользователь успешно обновлен!");
            setVariant("success");
            setAlertShow(true);
            onEditComplete();
            onHide();
        } catch (error) {
            console.error("Ошибка при редактировании пользователя:", error);
            setAlertText("Ошибка при редактировании пользователя.");
            setVariant("danger");
            setAlertShow(true);
        }
    };

    return (
        <Modal show={show} onHide={onHide} centered>
            {alertShow && (
                <Alert
                    variant={variant}
                    onClose={() => setAlertShow(false)}
                    dismissible
                >
                    {alertText}
                </Alert>
            )}
            <Modal.Header closeButton>
                <Modal.Title>Редактировать пользователя</Modal.Title>
            </Modal.Header>
            <Modal.Body>
                <Form>
                    <Form.Group>
                        <Form.Label>Имя пользователя</Form.Label>
                        <Form.Control
                            value={name}
                            onChange={(e) => setName(e.target.value)}
                        />
                    </Form.Group>
                    <Form.Group>
                        <Form.Label>Информация</Form.Label>
                        <Form.Control
                            value={info}
                            onChange={(e) => setInfo(e.target.value)}
                        />
                    </Form.Group>
                </Form>
            </Modal.Body>
            <Modal.Footer>
                <Button variant="secondary" onClick={onHide}>
                    Закрыть
                </Button>
                <Button variant="primary" onClick={handleEdit}>
                    Сохранить
                </Button>
            </Modal.Footer>
        </Modal>
    );
};

export default EditUser;
