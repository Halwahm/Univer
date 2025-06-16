/* eslint-disable jsx-a11y/anchor-is-valid */
/* eslint-disable jsx-a11y/alt-text */
import {useEffect, useState} from "react";
import {Buffer} from "buffer";
import {useNavigate} from "react-router-dom";
import {
  AspectRatio,
  Badge,
  Card,
  Center,
  Divider,
  Group,
  Image,
  Loader,
  Paper,
  SimpleGrid,
  Stack,
  Text,
  useMantineTheme,
} from '@mantine/core';
import {IconCalendar, IconClock, IconMovie, IconUser} from "@tabler/icons-react";
import {getHumanReadableGenre} from "../../utils/genreUtils";

function TablePag({ data }) {
  const navigate = useNavigate();
  const theme = useMantineTheme();
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    // Имитация загрузки для плавного появления
    const timer = setTimeout(() => setLoading(false), 300);
    return () => clearTimeout(timer);
  }, [data]);

  function handleClick(id) {
    navigate("/Film", { state: { ID: id } });
  }

  const formatDuration = (duration) => {
    if (!duration) return "Не указано";
    const [hours, minutes] = duration.split(':');
    return `${hours} ч ${minutes} мин`;
  };

  if (loading) {
    return (
      <Center py="xl">
        <Loader size="xl" variant="dots" />
      </Center>
    );
  }

  return (
    <SimpleGrid
      cols={3}
      spacing="lg"
      breakpoints={[
        { maxWidth: 'md', cols: 2, spacing: 'md' },
        { maxWidth: 'sm', cols: 1, spacing: 'sm' },
      ]}
    >
      {data?.map((item) => (
        <Card
          key={item.id}
          shadow="sm"
          padding="lg"
          radius="md"
          withBorder
          style={{
            cursor: 'pointer',
            transition: 'all 0.2s ease',
            '&:hover': {
              transform: 'translateY(-5px)',
              boxShadow: theme.shadows.md,
            }
          }}
          onClick={() => handleClick(item.id)}
        >
          <Card.Section>
            <AspectRatio ratio={9/12} mx="auto">
              <Image
                src={`data:image/jpeg;base64,${Buffer.from(item?.img?.data || '').toString("base64")}`}
                alt={item.name || 'Название фильма'}
                radius="md"
                // fit="cover"
                // withPlaceholder
                // placeholder={
                //   <Center>
                //     <Loader />
                //   </Center>
                // }
              />
            </AspectRatio>
          </Card.Section>

          <Stack mt="md" justify="space-between" h="100%">
            <Stack>
            <Group position="apart">
              <Text size="lg" fw={700} lineClamp={1}>
                {item.name || 'Без названия'}
              </Text>
              <Badge size="lg" variant="light">
                {getHumanReadableGenre(item.genre?.name || '')}
              </Badge>
            </Group>

            <Divider />

            <Stack spacing="xs">
              <Group spacing="xs">
                <IconClock size="1rem" color={theme.colors.blue[6]} />
                <Text size="sm">
                  Длительность: <strong>{formatDuration(item.duration)}</strong>
                </Text>
              </Group>
              <Group spacing="xs">
                <IconCalendar size="1rem" color={theme.colors.blue[6]} />
                <Text size="sm">
                  Год выпуска: <strong>{item.year || 'Не указан'}</strong>
                </Text>
              </Group>
              <Group spacing="xs">
                <IconUser size="1rem" color={theme.colors.blue[6]} />
                <Text size="sm">
                  Возрастное ограничение: <strong>{item.ageLimit || '0'}+</strong>
                </Text>
              </Group>
            </Stack>

            <Divider />

            <Text size="sm" color="dimmed" lineClamp={2}>
              {item.description || 'Описание отсутствует'}
            </Text>
            </Stack>
            <Stack>
            <Paper p="xs" radius="md">
              <Group spacing="xs">
                <IconMovie size="1rem" color={theme.colors.blue[6]} />
                <Text size="sm" fw={500}>

                    {item.startRelease ? new Date(item.startRelease).toLocaleDateString() : 'Не указано'} - {' '}
                    {item.endRelease ? new Date(item.endRelease).toLocaleDateString() : 'Не указано'}

                </Text>
              </Group>
            </Paper>
            </Stack>
          </Stack>
        </Card>
      ))}
    </SimpleGrid>
  );
}

export default TablePag;
