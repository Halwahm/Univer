/* eslint-disable default-case */
/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, {useEffect, useState} from "react";
import {
  ActionIcon,
  Alert,
  Button,
  Container,
  Grid,
  Group,
  LoadingOverlay,
  Modal,
  Paper,
  Select,
  Stack,
  Table,
  Text,
  TextInput,
  Title,
} from "@mantine/core";
import {IconAlertCircle, IconTrash} from "@tabler/icons-react";
import {notifications} from "@mantine/notifications";
import Store from "../../../store/store";

const AdminAddSession = () => {
  const store = new Store();
  const [loading, setLoading] = useState(true);
  const [sessions, setSessions] = useState([]);
  const [films, setFilms] = useState([]);
  const [halls, setHalls] = useState([]);
  const [selectedSession, setSelectedSession] = useState(null);
  const [deleteModal, setDeleteModal] = useState(false);
  const [formErrors, setFormErrors] = useState([]);
  const [formData, setFormData] = useState({
    filmId: "",
    hallId: "",
    dateSession: "",
    timeSession: "",
  });

  useEffect(() => {
    fetchData();
  }, []);

  const fetchData = async () => {
    try {
      const [sessionsRes, filmsRes, hallsRes] = await Promise.all([
        store.GetSession(),
        store.GetFilm(),
        store.GetAllHall(),
      ]);

      setSessions(sessionsRes.data || []);
      setFilms(filmsRes.data || []);
      setHalls(hallsRes.data || []);
    } catch (error) {
      console.error('Error fetching data:', error);
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось загрузить данные',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setFormErrors([]); // Очищаем предыдущие ошибки
    
    try {
      const sessionData = {
        timeSession: formData.timeSession,
        film: formData.filmId,
        hall: formData.hallId,
        dateSession: formData.dateSession
      };

      const response = await store.AddSession(sessionData);
      if (response.data) {
        notifications.show({
          title: 'Успех',
          message: 'Сеанс успешно добавлен',
          color: 'green',
        });
        fetchData();
        setFormData({
          filmId: "",
          hallId: "",
          dateSession: "",
          timeSession: "",
        });
      }
    } catch (error) {
      if (error.response?.data?.message) {
        const errorMessages = Array.isArray(error.response.data.message) 
          ? error.response.data.message 
          : [error.response.data.message];
        
        const formattedErrors = errorMessages.map(message => {
          const [field, msg] = message.split(':').map(s => s.trim());
          return msg || message;
        });
        
        setFormErrors(formattedErrors);
      } else {
        setFormErrors(['Не удалось добавить сеанс']);
      }
    }
  };

  const handleDelete = async () => {
    try {
      const response = await store.DeleteSession(selectedSession.id);
      if (response.data) {
        notifications.show({
          title: 'Успех',
          message: 'Сеанс успешно удален',
          color: 'green',
        });
        fetchData();
        setDeleteModal(false);
        setSelectedSession(null);
      }
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось удалить сеанс',
        color: 'red',
      });
    }
  };

  const openDeleteModal = (session) => {
    setSelectedSession(session);
    setDeleteModal(true);
  };

  if (loading) {
    return (
      <Container size="xl" py="xl">
        <LoadingOverlay visible={true} />
      </Container>
    );
  }

  return (
    <Container size="xl" py="xl">
      <Stack spacing="xl">
        <Paper p="md" radius="md" withBorder>
          <Title order={3} mb="md">Добавить новый сеанс</Title>
          {formErrors.length > 0 && (
            <Alert 
              icon={<IconAlertCircle size="1rem" />}
              title="Ошибка"
              color="red"
              mb="md"
              variant="filled"
            >
              {formErrors.map((error, index) => (
                <Text key={index} size="sm" color="white">
                  {error}
                </Text>
              ))}
            </Alert>
          )}
          <form onSubmit={handleSubmit}>
            <Grid>
              <Grid.Col span={{ base: 12, sm: 6 }}>
                <Select
                  label="Фильм"
                  placeholder="Выберите фильм"
                  data={films.map(film => ({ value: film.id, label: film.name }))}
                  value={formData.filmId}
                  onChange={(value) => {
                    setFormData({ ...formData, filmId: value });
                    setFormErrors([]); // Очищаем ошибки при изменении полей
                  }}
                  required
                />
              </Grid.Col>
              <Grid.Col span={{ base: 12, sm: 6 }}>
                <Select
                  label="Зал"
                  placeholder="Выберите зал"
                  data={halls.map(hall => ({ value: hall.id, label: hall.name }))}
                  value={formData.hallId}
                  onChange={(value) => {
                    setFormData({ ...formData, hallId: value });
                    setFormErrors([]);
                  }}
                  required
                />
              </Grid.Col>
              <Grid.Col span={{ base: 12, sm: 6 }}>
                <TextInput
                  label="Дата"
                  type="date"
                  value={formData.dateSession}
                  onChange={(e) => {
                    setFormData({ ...formData, dateSession: e.target.value });
                    setFormErrors([]);
                  }}
                  required
                />
              </Grid.Col>
              <Grid.Col span={{ base: 12, sm: 6 }}>
                <TextInput
                  label="Время"
                  type="time"
                  value={formData.timeSession}
                  onChange={(e) => {
                    setFormData({ ...formData, timeSession: e.target.value });
                    setFormErrors([]);
                  }}
                  required
                />
              </Grid.Col>
              <Grid.Col span={12}>
                <Button type="submit">
                  Добавить сеанс
                </Button>
              </Grid.Col>
            </Grid>
          </form>
        </Paper>

        <Paper p="md" radius="md" withBorder>
          <Title order={3} mb="md">Список сеансов</Title>
          <Table striped highlightOnHover withColumnBorders>
            <Table.Thead>
              <Table.Tr>
                <Table.Th>Фильм</Table.Th>
                <Table.Th>Дата</Table.Th>
                <Table.Th>Время</Table.Th>
                <Table.Th>Зал</Table.Th>
                <Table.Th>Действия</Table.Th>
              </Table.Tr>
            </Table.Thead>
            <Table.Tbody>
              {sessions.map((session) => (
                <Table.Tr key={session.id}>
                  <Table.Td>{session.film.name}</Table.Td>
                  <Table.Td>{new Date(session.dateSession).toLocaleDateString()}</Table.Td>
                  <Table.Td>{session.timeSession}</Table.Td>
                  <Table.Td>{session.hall.name}</Table.Td>
                  <Table.Td>
                    <ActionIcon
                      color="red"
                      variant="light"
                      onClick={() => openDeleteModal(session)}
                    >
                      <IconTrash size="1rem" />
                    </ActionIcon>
                  </Table.Td>
                </Table.Tr>
              ))}
            </Table.Tbody>
          </Table>
        </Paper>
      </Stack>

      <Modal
        opened={deleteModal}
        onClose={() => {
          setDeleteModal(false);
          setSelectedSession(null);
        }}
        title="Удалить сеанс"
        size="md"
      >
        <Stack spacing="md">
          <Text>Вы уверены, что хотите удалить этот сеанс?</Text>
          <Group position="right">
            <Button variant="default" onClick={() => setDeleteModal(false)}>
              Отмена
            </Button>
            <Button color="red" onClick={handleDelete}>
              Удалить
            </Button>
          </Group>
        </Stack>
      </Modal>
    </Container>
  );
};

export default AdminAddSession;
