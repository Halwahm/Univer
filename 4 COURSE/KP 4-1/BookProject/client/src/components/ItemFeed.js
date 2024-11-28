import React, { useEffect, useState } from 'react';
import { observer } from 'mobx-react-lite';
import { Card } from 'react-bootstrap';
import { getUserInfo, deleteFeedback } from '../http/userAPI';
import { formatDate } from '../utils/const';

const ItemFeed = observer(({ data }) => {
  const [user, setUser] = useState({});
  const [isDeleted, setIsDeleted] = useState(false);

  useEffect(() => {
    const load = async () => {
      try {
        const response = await getUserInfo(data.ID_USER);
        setUser(response);
      } catch (e) {
        console.log(e);
      }
    };
    load();
  }, [data, isDeleted]);

  const deleteFeed = async () => {
    try {
      await deleteFeedback(data.ID);
      setIsDeleted(true);
    } catch (e) {
      console.log(e);
    }
  };

  if (!user) {
    return <div>Отзыв удален</div>;
  }

  const role = localStorage.getItem('role');

  return (
    <Card>
      {isDeleted && <div>Отзыв удален</div>}
      <div className="d-flex align-items-center" style={{ margin: '10px' }}>
        <div className="flex-shrink-0">
          <img
            src={`${process.env.REACT_APP_API_URL}/User${data.ID_USER}.jpg`}
            className="rounded-circle"
            style={{ width: '90px', height: '90px', objectFit: 'cover' }}
            alt="User avatar"
          />
        </div>
        <div className="flex-grow-1">
          <Card.Body className="px-3">
            <Card.Title>{user.USER_NAME}</Card.Title>
            <Card.Text>{data.FEEDBACK}</Card.Text>
            <Card.Text>{formatDate(data.DATE)}</Card.Text>
          </Card.Body>
        </div>
        <div className="flex-shrink-0">
          {role === 'ADMIN' && (
            <button
              className="btn btn-outline-danger"
              style={{
                width: '40px',
                height: '40px',
                marginLeft: '15px',
              }}
              onClick={deleteFeed}
            >
              Х
              <i className="bi bi-trash"></i>
            </button>
          )}
        </div>
      </div>
    </Card>
  );
});

export default ItemFeed;
