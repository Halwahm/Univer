import React, { useEffect } from "react";
import { Button, Modal, Form } from "react-bootstrap";
import { observer } from "mobx-react-lite";
import { update } from "../../http/userAPI";
import {  uploadFile } from "../../http/bookAPI";
import { Alert } from 'react-bootstrap';
import localforage from "localforage";

const UpdateUser = observer( (props) => {
  const [name, setName] = React.useState("");
  const [file, setFile] = React.useState(null);
  const [info, setInfo] = React.useState([])

  let [alertshow, setAlertshow] = React.useState(false);
  const [variant, setVariant] = React.useState('success');
  const [alertText, setAlertText] = React.useState('Успешно');


    useEffect(() => {
        setName(props.user.USER_NAME)
        setInfo(props.user.USER_INFO)
    }, [props.user.USER_NAME, props.user.USER_INFO])
    
    const updateU = async() => {
        
        if(name.trim() === "" || info.trim() === ""){
            setAlertshow(true);
            setVariant('danger');
            setAlertText('Заполните все поля');
        }else {
        setAlertshow(false);
        if(file !== null && file.type == 'image/jpeg'){
            const formData = new FormData();
        formData.append('name','User' + props.user.ID + '.jpg');
        formData.append('file', file);
          let data = await uploadFile(formData)
        }
        setAlertshow(false);
        let upuser = await update(props.user.ID, name, info)
        //Перезагрузка страницы
        localStorage.setItem('name', name);
        window.location.reload();
      }
        
        
    
  }
    return (
      <Modal
      {...props}
      size="lg"
      aria-labelledby="contained-modal-title-vcenter"
      centered >
        {alertshow && <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>{alertText}</Alert>}
        <Modal.Header closeButton>
        
        <Modal.Title id="contained-modal-title-vcenter">
          Изменить профиль
        </Modal.Title>
      </Modal.Header>
      <Modal.Body>
        <Form>
          <Form.Control 
            value={name}
            onChange={e => setName(e.target.value)}
          placeholder="Введите новое имя" />
            <Form.Control
            className="mt-3"
            type="file"
            onChange={e => setFile(e.target.files[0])}
            />
            <Form.Control
            className="mt-3"
            value={info}
            onChange={e => setInfo(e.target.value)}
            placeholder="Введите информацию о себе" />

        </Form>
      </Modal.Body>
      <Modal.Footer>
        <Button onClick={props.onHide}>Close</Button>
        <Button onClick={updateU}>Save</Button>
      </Modal.Footer>
    </Modal>
    );
})

export default UpdateUser;