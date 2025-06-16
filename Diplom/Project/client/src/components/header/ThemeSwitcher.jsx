import React from 'react';
import {ActionIcon, useComputedColorScheme, useMantineColorScheme} from '@mantine/core';
import {IconMoon, IconSun} from '@tabler/icons-react';

function Demo() {
    const { setColorScheme } = useMantineColorScheme();
    const computedColorScheme = useComputedColorScheme('light', { getInitialValueInEffect: true });

    const handleClick = () => {
        setColorScheme(computedColorScheme === 'light' ? 'dark' : 'light');
    };

    return (
        <ActionIcon
            onClick={handleClick}
            variant="default"
            size="xl"
            radius="xl"
            aria-label="Toggle color scheme"
            style={{ cursor: 'pointer' }}
        >
            {computedColorScheme === 'light' ? (
                <IconSun style={{ stroke: '0.2', color: 'black' }} />
            ) : (
                <IconMoon style={{ stroke: '0.2', color: 'white' }} />
            )}
        </ActionIcon>
    );
}

export default Demo;
