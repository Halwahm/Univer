   M S B A M L   `   `   `  ����B  >WpfApp1, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:WpfApp1WpfApp1  5   	       WpfApp1.loginWindow   5   	   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   _ [MaterialDesignThemes.Wpf, Version=4.9.0.0, Culture=neutral, PublicKeyToken=df2a72020bd7962aFmaterialDesign1http://materialdesigninxaml.net/winfx/xaml/themes  5   	   !localclr-namespace:WpfApp1  5   	   -   5          � Icon$*  $/Resources/images/loading_screen.png��5	   	    � Title$ authentication��5
   	   $	��550��6    $	��700��6-   .��5      � ���#CCCCFF.+�5   
   �� $	��400��6   $��15,59,14.6,59q�6    
�������$��Center=�6K    �� Padding$ 30q�6f   $	��550��6s    �� CornerRadius$ 20��6�   $��2��6�    J� Effect 5      3  -System.Windows.Media.Effects.DropShadowEffect  5         
BlurRadius$ 50Q�6#      Color$
 Gray��63      ShadowDepth$ 10Q�6@   ._�5      �� .+�5      �� $0��*Добро пожаловать в SushiHm��6   $��25(�6>   $��
ExtraBlack"�6L   $��Center=�6d   $��0 0 0 0q�6�   �� 5      $A��;Введите ваши данные, чтобы войти��6   $��23(�6E   $
��Bold"�6S   $��Center=�6e   $��0 0 0 0q�6�   �� 5      $E��?или зарегистрируйте новый аккаунт��6   $��23(�6F   $
��Bold"�6T   $��Center=�6f   $��0,0,0,20q�6�   � 5      $��0 0 0 20q�6   .+�5      �� -   5        $
��Left=�5      $*��$Зарегестрироваться��68   6U   �� 5      $��Right=�6   $��Вход��69      MaterialDesignFlatButton#��[  6H   5      �� 5      -   5         ��Name$ textBoxEmail��5   )   	 �� 	MaxLength$	 30��6   )  #MaterialDesignThemes.Wpf.HintAssist
   Hint$!
 Введите ваш email��6?    % !MaterialDesignFloatingHintTextBox#��[ 6r   G� 5      -   5         G�Name$ passwordBox��5   -    G� 	MaxLength$ 15��6   $(
 "Введите ваш пароль��6B    ) %MaterialDesignFloatingHintPasswordBox#��[ 6v   �� 5      -   5         ��Name$ signInButton��5   )   $��
Войти��6   $
��0 20q�6?   6M   5      5       5!      5"      