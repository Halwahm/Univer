import React, { useState } from 'react';
import { Button, Modal, Form, Alert } from 'react-bootstrap';
import { createGenre } from '../../http/bookAPI';
import { Formik, Field, ErrorMessage } from 'formik';

const CreateGenre = (props) => {
  const [alertshow, setAlertshow] = useState(false);
  const [variant, setVariant] = useState('success');
  const [alertText, setAlertText] = useState('Успешно');

  const addGenre = async (values) => {
    try {
      const response = await createGenre({ name: values.value });
      console.log(response);
      setAlertshow(false);
      props.onHide();
    } catch (error) {
      setAlertshow(true);
      setVariant('danger');
      setAlertText('Произошла ошибка возможно такой жанр уже существует');
    }
  };

  return (
    <Modal {...props} size="lg" aria-labelledby="contained-modal-title-vcenter" centered>
      {alertshow && (
        <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>
          {alertText}
        </Alert>
      )}
      <Modal.Header closeButton>
        <Modal.Title id="contained-modal-title-vcenter">Создать жанр</Modal.Title>
      </Modal.Header>
      <Modal.Body>
        <Formik
          initialValues={{ value: '' }}
          validate={(values) => {
            const errors = {};
            if (!values.value) {
              errors.value = 'Введите название жанра';
            }
            return errors;
          }}
          onSubmit={addGenre}
        >
          {({ values, handleChange, handleSubmit, errors }) => (
            <Form noValidate onSubmit={handleSubmit}>
              <Field
                type="text"
                name="value"
                value={values.value}
                onChange={handleChange}
                placeholder="Введите название жанра"
                as={Form.Control}
                isInvalid={!!errors.value}
              />
              <ErrorMessage name="value" component={Form.Control.Feedback} type="invalid" />
              <Button type="submit">Создать</Button>
            </Form>
          )}
        </Formik>
      </Modal.Body>
    </Modal>
  );
};

export default CreateGenre;
