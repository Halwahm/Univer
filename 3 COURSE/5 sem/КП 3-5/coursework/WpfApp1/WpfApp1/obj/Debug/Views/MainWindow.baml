   M S B A M L   `   `   `  ����B  >WpfApp1, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:WpfApp1WpfApp1  5   	       WpfApp1.MainWindow   5   	   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   _ [MaterialDesignThemes.Wpf, Version=4.9.0.0, Culture=neutral, PublicKeyToken=df2a72020bd7962aFmaterialDesign1http://materialdesigninxaml.net/winfx/xaml/themes  5   	   !localclr-namespace:WpfApp1  5   	   -   5          � Icon$*  $/Resources/images/loading_screen.png��5
   	    � Title$ authentication��5   	   $	��650��6    $	��800��6-   .��5      � ���#CCCCFF � ColumnDefinitions 5   
   �� 5      $
��211* �6   �� 5      $
��186* �6   .+�5   
   �� $	��400��6   $��15,59,14.6,59q�6    
�������$��Center=�6K    �� Padding$ 30q�6f   $	��550��6s    �� CornerRadius$ 20��6�   $��2��6�    J� Effect 5      3  -System.Windows.Media.Effects.DropShadowEffect  5         
BlurRadius$ 40Q�6#      Color$
 Gray��63      ShadowDepth$ 10Q�6@   ._�5      �� .+�5      �� $@��:Добро пожаловать в магазин суши��6   $��24(�6C   $
��Bold"�6Q   $��Center=�6c   $��0 0 0 20q�6�   � 5      $��0 0 0 20q�6   .+�5      �� $
��Left=�6   $��Регистрация��68      MaterialDesignFlatButton#��[  6N   �� 5      -   5        $��Right=�5      $��
Войти��69   6I   5      �� 5      -   5        	 ��Name$	 textBoxEmail��5   )   
 �� 	MaxLength$
 30��6   )  #MaterialDesignThemes.Wpf.HintAssist   Hint$! Введите ваш email��6?    % !MaterialDesignFloatingHintTextBox#��[ 6r   �� 5      -   5        $	 textBoxName��5   )   $
 15��6   $$ Введите ваше имя��6>   #��[ 6p   �� 5      -   5        $	 textBoxLastName��5   )   $
 15��6   $, &Введите вашу фамилию��6B   #��[ 6x   �� 5      -   5        $	 textBoxAddress��5   )   $
 50��6   $&  Введите ваш адрес��6A   #��[ 6t   �� 5       -   5        $	 textBoxPhoneNumber��5    )   $
 14��6   $7 1Введите ваш номер телефона��6E   #��[ 6�   G� 5!      -   5         G�Name$ passwordBox��5!   -    G� 	MaxLength$ 15��6   $( "Введите ваш пароль��6B    ) %MaterialDesignFloatingHintPasswordBox#��[ 6v   G� 5"      -	   5        $ passwordBox2��5"   -   $ 15��6   $8 2Повторите введенный пароль��6C   #��[ 6   �� 5#      -
   5         ��Name$ registerButton��5#   6   $*��$Зарегистрироваться��6   $
��0 20q�6N   6\   5$      5%      5&      5'      