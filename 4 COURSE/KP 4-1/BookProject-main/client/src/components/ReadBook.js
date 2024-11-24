import React, { useEffect, useState, useRef } from 'react';
import { ReactReader } from 'react-reader';
import { Container, Card } from 'react-bootstrap';
import { observer } from 'mobx-react-lite';
import { updateMarks } from '../http/userAPI';
import { Alert } from 'react-bootstrap';
import ePub from 'epubjs';

const ReadBook = observer(({ data }) => {
  const defaultLocation = { start: 0 };
  const [location, setLocation] = useState(localStorage.getItem('bookProgress') || JSON.stringify(defaultLocation))
  const renditionRef = useRef(null)
  const tocRef = useRef(null)

  console.log(location)

  let [alertshow, setAlertshow] = React.useState(false);
  const [variant, setVariant] = React.useState('success');
  const [alertText, setAlertText] = React.useState('');
  console.log(data)

  const locationChanged = epubcifi => {
    if (renditionRef.current && tocRef.current) {
      console.log(epubcifi)
      try {
        const { displayed, href } = renditionRef.current.location
        const chapter = tocRef.current.find(item => item.href === href)
        
        localStorage.setItem('bookProgress', epubcifi)
        updateMarks(localStorage.getItem('id'), data, epubcifi)
        setLocation(epubcifi)
      }
      catch (e) {
        console.log(e)
        setAlertshow(true);
        setVariant('danger');
        setAlertText('Произошла ошибка: ' + e);
      }
    }
  }

  return (
    <Card>
      {alertshow && <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>{alertText}</Alert>}
      <div style={{ height: '100vh' }}>
        <ReactReader
          locationChanged={locationChanged}
          {...location && { location }}
          url={process.env.REACT_APP_API_URL + 'Book' + data + '.epub'}
          getRendition={rendition => (renditionRef.current = rendition)}
          tocChanged={toc => (tocRef.current = toc)}
        />
      </div>
    </Card>
  )
});

export default ReadBook;