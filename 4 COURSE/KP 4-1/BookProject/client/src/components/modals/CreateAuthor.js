import React, { useState } from "react";
import { Button, Modal, Form, Alert } from "react-bootstrap";
import { Formik, Field, ErrorMessage } from "formik";
import { $authHost } from "../../http/index";

const CreateAuthor = (props) => {
  const [alertShow, setAlertShow] = useState(false);
  const [variant, setVariant] = useState("success");
  const [alertText, setAlertText] = useState("");

  // Функция для назначения роли AUTHOR
  const assignAuthorRole = async (values, { resetForm }) => {
    try {
      // Запрос на сервер
      const { data } = await $authHost.put("api/users/change-role", {
        email: values.email,
      });
      setAlertText(data.message);
      setVariant("success");
      setAlertShow(true);
      resetForm();
      props.onHide();
    } catch (error) {
      setAlertText(error.response?.data?.message || "Произошла ошибка.");
      setVariant("danger");
      setAlertShow(true);
    }
  };

  return (
    <Modal
      {...props}
      size="lg"
      aria-labelledby="contained-modal-title-vcenter"
      centered
    >
      {alertShow && (
        <Alert
          variant={variant}
          className="mt-3"
          onClose={() => setAlertShow(false)}
          dismissible
        >
          {alertText}
        </Alert>
      )}
      <Modal.Header closeButton>
        <Modal.Title id="contained-modal-title-vcenter">
          Назначить пользователя автором
        </Modal.Title>
      </Modal.Header>
      <Modal.Body>
        <Formik
          initialValues={{ email: "" }}
          validate={(values) => {
            const errors = {};
            if (!values.email) {
              errors.email = "Введите email пользователя.";
            } else if (
              !/^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}$/i.test(values.email)
            ) {
              errors.email = "Некорректный email.";
            }
            return errors;
          }}
          onSubmit={assignAuthorRole}
        >
          {({ handleSubmit, handleChange, values, errors }) => (
            <Form noValidate onSubmit={handleSubmit}>
              <Field
                type="email"
                name="email"
                placeholder="Введите email пользователя"
                as={Form.Control}
                isInvalid={!!errors.email}
                onChange={handleChange}
                value={values.email}
              />
              <ErrorMessage
                name="email"
                component={Form.Control.Feedback}
                type="invalid"
              />
              <Button type="submit" className="mt-3">
                Назначить автором
              </Button>
            </Form>
          )}
        </Formik>
      </Modal.Body>
    </Modal>
  );
};

export default CreateAuthor;
