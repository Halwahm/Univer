   M S B A M L   `   `   `  ����B  >WpfApp1, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null5clr-namespace:WpfApp1.viewmodelWpfApp1.viewmodel  5          WpfApp1.OrderedPage   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      5	viewmodelclr-namespace:WpfApp1.viewmodel     5        N� Title$  OrderedPage��5
      .��5      � .+�5   
   �� ��6   �� *OrderedProducts+ �� SelectedItem 6:   �� *OrderedProduct+ �� UpdateSourceTrigger$ PropertyChanged=���5      �� 5      .R�5      � $	��Top=�6    $��Center=�68   5      ��5      �� 5      .R�5      ��  �� Orientation$ 
Horizontal=�6!   $��0,0,0,5q�6:   .+�5      �  � ColumnDefinitions 5      �� 5   "   $
��Auto �63   �� 5   "   $
��Auto �63   �� 5   "   $
��Auto �63   �� 5   "   $
��Auto �63    � RowDefinitions 5      �� 5   "   $
��Auto �60   �� 5   "   $
��Auto �60   �� 5    "   $
��Auto �60   �� 5!   "   $
��Auto �60   .+�5$      �� $��0��6(   $��0��68   $��Id��6E   
���   �$��16(�6b   $
��Bold"�6p   $��5q�6�   �� 5%      $��1��6(   $��0��68   
���   �$��16(�6q   $
��Bold"�6   $��5q�6�   ��6E   �� *	OrderID+6�   �� 5'      $��0��6(   $��1��68   $��Статус��6E   
���   �$��16(�6f   $
��Bold"�6t   $��5q�6�   �� 5(      $��1��6(   $��1��68   
��� � �$��16(�6p   $��5q�6~   ��6E   �� *Status+6~   �� 5*      $��0��6(   $��2��68   $��Стоимость��6E   
���   �$��16(�6i   $
��Bold"�6w   $��5q�6�   �� 5+      $��1��6(   $��2��68   
���   �$��16(�6�   $��15 5 0 0q�6�   ��6E   �� *
TotalPrice+ �� StringFormat$ {0:F2}��6�   �� 5-      $��0��6(   $��3��68   $��Товары��6E   
���   �$��16(�6f   $
��Bold"�6t   $��5q�6�   �� 5.      $��1��6(   $��3��68   
���   �$��16(�6u   $��5q�6�   $
��Wrap=�5/   !   $��CharacterEllipsis=�65   $	��100��6V   ��5.   E   �� *ProductName+5/   V   51      �� 53      $!��Отменить заказ��54      $��25,5,5,5q�56      
��� ���$��Right=�58      ��53   !   �� *DataContext.DelOrdered+ �� RelativeSource ��  �� AncestorType" ����55      �� 58      59      5;      ��5=      �� 5>      	 �� 
TargetType"	 ��6   .�5?      �� 
 �� Property
 � �� �� Value$ 0,0,0,5q�6/   �� 5@      
 � ��$ 0,0,0,1q�68   �� 5A      
 � ��
 �   �64   5B      5D      5E      5F      