import React, { useState } from 'react';
import { Button, Modal, Form, Alert } from 'react-bootstrap';
import { createTag } from '../../http/bookAPI';
import { Formik, Field, ErrorMessage } from 'formik';

const CreateTag = (props) => {
    const [alertshow, setAlertshow] = useState(false);
    const [variant, setVariant] = useState('success');
    const [alertText, setAlertText] = useState('Успешно');

    const addTag = async (values) => {
        try {
            const result = await createTag({ name: values.value });
            setAlertshow(false);
            props.onHide();
        } catch (error) {
            setAlertshow(true);
            setVariant('danger');
            setAlertText('Возможно такой тег уже существует');
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
                <Modal.Title id="contained-modal-title-vcenter">Создать тег</Modal.Title>
            </Modal.Header>
            <Modal.Body>
                <Formik
                    initialValues={{ value: '' }}
                    validate={(values) => {
                        const errors = {};
                        if (!values.value) {
                            errors.value = 'Введите название тега';
                        }
                        return errors;
                    }}
                    onSubmit={addTag}
                >
                    {({ values, handleChange, handleSubmit, isSubmitting, errors }) => (
                        <Form noValidate onSubmit={handleSubmit}>
                            <Field
                                type="text"
                                name="value"
                                value={values.value}
                                onChange={handleChange}
                                placeholder="Введите название тега"
                                as={Form.Control}
                                isInvalid={!!errors.value}
                                className="mb-2"
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

export default CreateTag;
