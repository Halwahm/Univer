   M S B A M L   `   `   `  ����B  >WpfApp1, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null!clr-namespace:WpfApp1WpfApp1  5      5clr-namespace:WpfApp1.viewmodelWpfApp1.viewmodel  5	          WpfApp1.Comments   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      'localclr-namespace:WpfApp1     5      5	viewmodelclr-namespace:WpfApp1.viewmodel     5	      _ [MaterialDesignThemes.Wpf, Version=4.9.0.0, Culture=neutral, PublicKeyToken=df2a72020bd7962aFmaterialDesign1http://materialdesigninxaml.net/winfx/xaml/themes  5
        N� Title$  Comments��5      .��5      �  � RowDefinitions 5   
   �� 5      $��40 �6   �� 5      $	��415 �6   �� 5      $��40 �6   .+�5   
   �� $��0��6   $-��'Оставьте комментарий��6   
���   �$��20(�6O   $
��Left=�6]   d� 5   
      StylesToogle#���   6;   $	��Top=�6c   $��Right=�6{   $��5q�6�   $��24(�6�   
���������6   �� *ShowCommentText+ d� 	IsChecked 6�   ��  �� Path$ 
IsSelected� �� Mode$ TwoWay=� �� RelativeSource ��  �� AncestorType" ��.��5      '  !MaterialDesignThemes.Wpf.PackIcon     Kind$ Close=�6&   
���   �$��5q�6F   $��20��6S   $��20��6_   5      �� 5   
   $��1��6   ��6   �� *SelectedProductCommentsList+��5      �� 5      .R�5      � $	��Top=�6    $��Center=�68   5      ��5      �� 5       .R�5!      ��  �� CornerRadius$ 3��6   $��2q�6.   
����  �._�5"      �� 
�������$	��300��6;   .+�5#      �� 	 �� Padding$	 5q�6(   �� 5$   "   $#�Id пользователя: ��6&   
���iii�6?    �� 5%   "   
���iii��6&   �� *
ClientID+6@   5&      �� 5'      
���   �$	 5q�6X   $
��Wrap=�6d   ��6(   �� *CommentText+6d   �� 5(      $��5q�5)   >   ��5(   %   �� *DataContext.DeleteComment+ �� " ����5)   !   �� .��5*   "     $ Delete=�6:   
���   �6H   5+      5,      5-      5.      50      � 54   
   $��2��6   $��Bottom=�6   
 � ColumnDefinitions
 55      �� 56      $��5* �6#   �� 57      $��* �6#   .+�59      �� $��0��6   $	��300��6&    �� 	MaxLength$	 250��62    �� TextWrapping$
 Wrap=�6�   
���   �$��20(�6�   $
��Left=�6�   
��� �����6B   �� *NewCommentText+ �� UpdateSourceTrigger$ PropertyChanged=�6�   �� 5:      $��1��69   $��50��6I   $��40��6T   $��Right=�6`   $��0q�6|   ��6   �� *AddCommentText+.��5;        $ CommentAddOutline=�6*   $��0q�6C   $��0q�6O   5<      5=      5>      5?      