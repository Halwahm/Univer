import React, { useState, useEffect, useContext } from 'react';
import { Table, Pagination } from 'react-bootstrap';
import { PrismaClient } from '@prisma/client';
import { featchUsers } from '../http/userAPI';
import { fetchBook, fetchGanre, fetchTags, fetchAuthor, deleteBook, delAuthor, delGanre, delTag } from '../http/bookAPI';
import { Button } from 'react-bootstrap';
import { BOOKS_ADMIN_ROUTE } from '../utils/const';
import { Context } from '../index';
import { Alert } from 'react-bootstrap';
import { deleteUser } from '../http/userAPI';
import { observer } from 'mobx-react-lite';

const DataTable = observer(({ schema, data, totalCount, page, setPage, actions }) => {
  const safeData = Array.isArray(data) ? data : [];

  if (!data || data.length === 0) {
      return <p>Нет данных для отображения</p>;
  }

  return (
    <Table striped bordered hover>
      <thead>
        <tr>
          {schema.map((column) => (
            <th key={column.field}>{column.label}</th>
          ))}
          {actions && <th>Действия</th>}
        </tr>
      </thead>
      <tbody>
        {safeData.map((row, index) => (
          <tr key={index}>
            {schema.map((column) => (
              <td key={`${index}-${column.field}`}>
                {row[column.field] !== undefined ? row[column.field] : ""}
              </td>
            ))}
            {actions && (
              <td>
                {actions.map((action, idx) => (
                  <Button
                    key={idx}
                    variant={action.variant || "primary"}
                    onClick={() => action.onClick(row)}
                    className="me-2"
                  >
                    {action.label}
                  </Button>
                ))}
              </td>
            )}
          </tr>
        ))}
      </tbody>
    </Table>
  );
});


export default DataTable;
