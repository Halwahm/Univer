/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, {useEffect, useState} from "react";
import {
  Avatar,
  Badge,
  Card,
  Container,
  Divider,
  Group,
  LoadingOverlay,
  Paper,
  Stack,
  Text,
  TextInput,
  Title,
} from "@mantine/core";
import {IconCalendar, IconClock, IconMovie, IconTicket, IconUser} from "@tabler/icons-react";
import Store from "../../../store/store";

const History = () => {
  const store = new Store();
  const [loading, setLoading] = useState(true);
  const [data, setData] = useState([]);
  const [searchQuery, setSearchQuery] = useState("");

  useEffect(() => {
    fetchData();
  }, []);

  const fetchData = async () => {
    try {
      const res = await store.GetHistory();
      setData(res.data || []);
    } catch (error) {
      console.error('Error fetching history:', error);
    } finally {
      setLoading(false);
    }
  };

  const filteredData = data.filter(item =>
    (item?.user?.name?.toLowerCase() || '').includes(searchQuery.toLowerCase()) ||
    (item?.user?.email?.toLowerCase() || '').includes(searchQuery.toLowerCase()) ||
    (item?.filmname?.toLowerCase() || '').includes(searchQuery.toLowerCase())
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
      <Stack spacing="xl">
        <Title order={1} className="h3 mb-3">
          <strong>История действий всех пользователей</strong>
        </Title>

        <Paper p="md" radius="md" withBorder>
          <Group position="apart" mb="xl">
            <Text className="card-title">CinemaDream</Text>
            <TextInput
              placeholder="Поиск по имени, email или фильму"
              value={searchQuery}
              onChange={(e) => setSearchQuery(e.target.value)}
              style={{ width: 300 }}
            />
          </Group>

          <Stack spacing="md">
            {filteredData.map((item) => (
              <Card key={item.id} shadow="sm" padding="lg" radius="md" withBorder>
                <Group position="apart" mb="xs">
                  <Group>
                    <Avatar color={item.OperationType === "Покупка билета" ? "green" : "red"} radius="xl">
                      <IconTicket size={20} />
                    </Avatar>
                    <Stack spacing={0}>
                      <Text weight={500}>{item.user.name}</Text>
                      <Text size="sm" color="dimmed">{item.user.email}</Text>
                    </Stack>
                  </Group>
                  <Badge
                    color={item.OperationType === "Покупка билета" ? "green" : "red"}
                    variant="light"
                  >
                    {item.OperationType}
                  </Badge>
                </Group>

                <Divider my="sm" />

                <Group position="apart" align="flex-start">
                  <Stack spacing="xs">
                    <Group spacing="xs">
                      <IconMovie size={16} color="gray" />
                      <Text size="sm">
                        <Text component="span" weight={500}>Фильм: </Text>
                        {item.filmname}
                      </Text>
                    </Group>
                    <Group spacing="xs">
                      <IconCalendar size={16} color="gray" />
                      <Text size="sm">
                        <Text component="span" weight={500}>Дата показа: </Text>
                        {new Date(item.date)
                          .getDate()
                          .toString()
                          .padStart(2, "0")}
                        .
                        {(new Date(item.date).getMonth() + 1)
                          .toString()
                          .padStart(2, "0")}
                        .
                        {new Date(item.date)
                          .getFullYear()
                          .toString()}
                      </Text>
                    </Group>
                  </Stack>

                  <Stack spacing="xs" align="flex-start">
                    <Group spacing="xs">
                      <IconUser size={16} color="gray" />
                      <Text size="sm" color="dimmed">
                        <Text component="span" weight={500}>Место: </Text>
                        {item.place}
                      </Text>
                    </Group>
                    <Group spacing="xs">
                      <IconClock size={16} color="gray" />
                      <Text size="sm" color="dimmed">
                        <Text component="span" weight={500}>Дата действия: </Text>
                        {new Date(item.datenow)
                          .getDate()
                          .toString()
                          .padStart(2, "0")}
                        .
                        {(new Date(item.datenow).getMonth() + 1)
                          .toString()
                          .padStart(2, "0")}
                        .
                        {new Date(item.datenow)
                          .getFullYear()
                          .toString()}
                      </Text>
                    </Group>
                  </Stack>
                </Group>
              </Card>
            ))}
          </Stack>
        </Paper>
      </Stack>
    </Container>
  );
};

export default History;
