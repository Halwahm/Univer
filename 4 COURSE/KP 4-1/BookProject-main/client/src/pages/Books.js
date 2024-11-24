import React, { useContext, useState } from "react";
import { Col, Container, Row } from "react-bootstrap";
import BooksList from "../components/BooksList";
import { observer } from "mobx-react-lite";
import { Context } from "../index";
import { useEffect } from "react";
import { fetchGanre, fetchBook } from "../http/bookAPI";

const Books = observer(() => {
        return (
        <Container>
            <Row>
                <Col md={100} className="mt-2">
                    <BooksList /> 
                </Col>
            </Row>
        </Container>
    );
}
)
export default Books;