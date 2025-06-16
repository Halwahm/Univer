import React, {useEffect, useState} from "react";
import {
  ActionIcon,
  Button,
  Container,
  Group,
  LoadingOverlay,
  Modal,
  Stack,
  Table,
  Text,
  TextInput,
  Title,
  Badge,
} from "@mantine/core";
import {IconTrash, IconLock, IconLockOpen} from "@tabler/icons-react";
import {notifications} from "@mantine/notifications";
import Store from "../../../store/store";

const AdminAllUsers = () => {
  const store = new Store();
  const [loading, setLoading] = useState(true);
  const [users, setUsers] = useState([]);
  const [selectedUser, setSelectedUser] = useState(null);
  const [deleteModal, setDeleteModal] = useState(false);
  const [blockModal, setBlockModal] = useState(false);
  const [searchQuery, setSearchQuery] = useState("");
  
  useEffect(() => {
    fetchData();
  }, []);
  
  const fetchData = async () => {
    try {
      const response = await store.GetUsers();
      setUsers(response.data || []);
    } catch (error) {
      console.error('Error fetching users:', error);
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось загрузить данные пользователей',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };
  
  const handleDelete = async () => {
    try {
      const response = await store.DeleteUser(selectedUser.id);
      if (response.data) {
        notifications.show({
          title: 'Успех',
          message: 'Пользователь успешно удален',
          color: 'green',
        });
        fetchData();
        setDeleteModal(false);
        setSelectedUser(null);
      }
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось удалить пользователя',
        color: 'red',
      });
    }
  };
  
  const handleBlockToggle = async () => {
    try {
      const response = selectedUser.status === "DisActive"
          ? await store.UnDeleteUser(selectedUser.id)
          : await store.DeleteUser(selectedUser.id);
      
      if (response.data) {
        notifications.show({
          title: 'Успех',
          message: selectedUser.status === "DisActive"
              ? 'Пользователь успешно разблокирован'
              : 'Пользователь успешно заблокирован',
          color: 'green',
        });
        fetchData();
        setBlockModal(false);
        setSelectedUser(null);
      }
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось изменить статус пользователя',
        color: 'red',
      });
    }
  };
  
  const openDeleteModal = (user) => {
    setSelectedUser(user);
    setDeleteModal(true);
  };
  
  const openBlockModal = (user) => {
    setSelectedUser(user);
    setBlockModal(true);
  };
  
  const filteredUsers = users.filter(user =>
      user.name.toLowerCase().includes(searchQuery.toLowerCase()) ||
      user.email.toLowerCase().includes(searchQuery.toLowerCase())
  );
  
  if (loading) {
    return (
        <Container size="xl" py="xl">
          <LoadingOverlay visible={true} />
        </Container>
    );
  }
  
  return (
      <Container size="xl" py="xl">
        <Group position="apart" mb="md">
          <Title order={3}>Список пользователей</Title>
          <TextInput
              placeholder="Поиск по имени или email"
              value={searchQuery}
              onChange={(e) => setSearchQuery(e.target.value)}
              style={{ width: 300 }}
          />
        </Group>
        
        <Table striped highlightOnHover withColumnBorders>
          <Table.Thead>
            <Table.Tr>
              <Table.Th>Имя</Table.Th>
              <Table.Th>Email</Table.Th>
              <Table.Th>Билетов куплено</Table.Th>
              <Table.Th>Билетов возвращено</Table.Th>
              <Table.Th>Роль</Table.Th>
              <Table.Th>Статус</Table.Th>
              <Table.Th>Действия</Table.Th>
            </Table.Tr>
          </Table.Thead>
          <Table.Tbody>
            {filteredUsers.map((user) => (
                <Table.Tr key={user.id}>
                  <Table.Td>{user.name}</Table.Td>
                  <Table.Td>{user.email}</Table.Td>
                  <Table.Td>{user.good}</Table.Td>
                  <Table.Td>{user.bad}</Table.Td>
                  
                  <Table.Td>
                    <Text
                        color={user.role === "Admin" ? "yellow" : "teal"}
                        weight={user.role === "Admin" ? 500 : 400}
                    >
                      {user.role}
                    </Text>
                  </Table.Td>
                  <Table.Td>
                    <Badge
                        color={user.status === "DisActive" ? "red" : "green"}
                        variant="light"
                    >
                      {user.status === "DisActive" ? "Заблокирован" : "Активен"}
                    </Badge>
                  </Table.Td>
                  <Table.Td>
                    <Group spacing="xs">
                      <ActionIcon
                          color={user.status === "DisActive" ? "green" : "red"}
                          variant="light"
                          onClick={() => openBlockModal(user)}
                          disabled={user.role === "Admin"}
                      >
                        {user.status === "DisActive" ? (
                            <IconLockOpen size="1rem" />
                        ) : (
                            <IconLock size="1rem" />
                        )}
                      </ActionIcon>
                    </Group>
                  </Table.Td>
                </Table.Tr>
            ))}
          </Table.Tbody>
        </Table>
        
        <Modal
            opened={blockModal}
            onClose={() => {
              setBlockModal(false);
              setSelectedUser(null);
            }}
            title={selectedUser?.status === "DisActive" ? "Разблокировать пользователя" : "Заблокировать пользователя"}
            size="md"
        >
          <Stack spacing="md">
            <Text>
              Вы уверены, что хотите {selectedUser?.status === "DisActive" ? "разблокировать" : "заблокировать"} пользователя {selectedUser?.name}?
            </Text>
            <Text size="sm" color="dimmed">
              {selectedUser?.status === "DisActive"
                  ? "Пользователь получит доступ к своему аккаунту."
                  : "Пользователь не сможет войти в свой аккаунт."}
            </Text>
            <Group position="right">
              <Button variant="default" onClick={() => setBlockModal(false)}>
                Отмена
              </Button>
              <Button
                  color={selectedUser?.status === "DisActive" ? "green" : "red"}
                  onClick={handleBlockToggle}
              >
                {selectedUser?.status === "DisActive" ? "Разблокировать" : "Заблокировать"}
              </Button>
            </Group>
          </Stack>
        </Modal>
      </Container>
  );
};

export default AdminAllUsers;