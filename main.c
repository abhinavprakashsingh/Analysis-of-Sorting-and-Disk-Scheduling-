#include<gtk/gtk.h>
#include<glib.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<lib/sort.h>
#include<lib/frwanalysis.h>
#include<lib/frandomgen.h>
#include<lib/charter.h>

void randomfilegen();
void load_file(GtkWidget *button,gpointer* win);
static void cb_changed( GtkComboBox *combo, gpointer data );
static void cb_delete( GtkButton *button, GtkComboBox *combo );
static gchar* ans=NULL;

int main(int argc,char **argv)
{
    GtkWidget       *window, *vbox ,*frame ,*combo ,*button ,*button1 ,*menubar ,*fileMenu, *fileMi , *quitMi ;
    GtkListStore    *store;
    GtkTreeIter      iter;
    GtkCellRenderer *cell;

    gtk_init( &argc, &argv );

    window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    g_signal_connect( G_OBJECT( window ), "destroy",
                      G_CALLBACK( gtk_main_quit ), NULL );
    gtk_container_set_border_width( GTK_CONTAINER( window ), 10 );
    gtk_window_set_default_size(window,500,500);

    vbox = gtk_vbox_new( FALSE, 6 );
    gtk_container_add( GTK_CONTAINER( window ), vbox );
    menubar = gtk_menu_bar_new();
    fileMenu = gtk_menu_new();

    //fileMi = gtk_menu_item_new_with_label("View");
    //quitMi = gtk_menu_item_new_with_label("About");

    //gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
   // gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
   // gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    frame = gtk_frame_new( " " );
    gtk_box_pack_start( GTK_BOX( vbox ), frame, FALSE, FALSE, 0 );


    store = gtk_list_store_new( 1, G_TYPE_STRING );


    gtk_list_store_append( store, &iter );
    gtk_list_store_set( store, &iter, 0, "Sorting", -1 );
    //gtk_list_store_append( store, &iter );
    //gtk_list_store_set( store, &iter, 0, "Searching", -1 );
    gtk_list_store_append( store, &iter );
    gtk_list_store_set( store, &iter, 0, "DiskScheduling", -1 );
    combo = gtk_combo_box_new_with_model( GTK_TREE_MODEL( store ) );
    gtk_container_add( GTK_CONTAINER( frame ), combo );


    g_object_unref( G_OBJECT( store ) );
    cell = gtk_cell_renderer_text_new();

    gtk_cell_layout_pack_start( GTK_CELL_LAYOUT( combo ), cell, TRUE );

    gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT( combo ), cell, "text", 0, NULL );

    g_signal_connect( G_OBJECT( combo ), "changed",
                      G_CALLBACK( cb_changed ), NULL );


    button = gtk_button_new_with_mnemonic( "Open file" );
    button1 = gtk_button_new_with_mnemonic( "Random test case generator" );
    gtk_box_pack_start( GTK_BOX( vbox ), button, FALSE, FALSE, 0 );
    gtk_box_pack_start( GTK_BOX( vbox ), button1, FALSE, FALSE, 0 );

    g_signal_connect( G_OBJECT( button ), "clicked",
                      G_CALLBACK( load_file ), (gpointer) window );

    //g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect( G_OBJECT( button1 ), "clicked",
                      G_CALLBACK(randomfilegen), (gpointer) window );


    gtk_window_set_title(GTK_WINDOW(window), "Tool");
    gtk_widget_show_all( window );
    gtk_main();

    return( 0 );
}

void randomfilegen()
{
	if(g_ascii_strcasecmp(ans,"sorting")==0)
	{
		printf("random-generation-sorting\n");
		frandomgen_main(0);
	}
	else if(g_ascii_strcasecmp(ans,"diskscheduling")==0)
	{
		printf("random-generation-diskscheduling\n");
		frandomgen_main(2);
	}		
}

void load_file(GtkWidget *button,gpointer* win)
{
    GtkWidget *dialog;
    dialog=gtk_file_chooser_dialog_new("FILE",GTK_WINDOW(win),
    GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,
    GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
    gtk_widget_show_all(dialog);
    gint response=gtk_dialog_run(GTK_DIALOG(dialog));
    if(response==GTK_RESPONSE_OK && g_ascii_strcasecmp(ans,"sorting")==0)
    {
        g_print("%s\n",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
		g_print("%s %d\n",ans, g_ascii_strcasecmp(ans,"sorting"));
		fileread_sort(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    }
    else 
    {
        g_print("canceled\n");
    }
    gtk_widget_destroy(dialog);

}

static void cb_changed( GtkComboBox *combo, gpointer data )
{
    GtkTreeIter   iter;
    gchar *string = NULL;

    GtkTreeModel *model;
    gchar *s="Sorting";
    if( gtk_combo_box_get_active_iter( combo, &iter ) )// sets the iterator to the current active item if it exists
    {
        model = gtk_combo_box_get_model( combo ); //Returns the GtkTreeModel which is acting as data source for combo_box .

        gtk_tree_model_get( model, &iter, 0, &string, -1 );//Gets the value of one or more cells in the row referenced by iter . The variable argument list should contain integer column numbers, each column number followed by a place to store the value being retrieved. The list is terminated by a -1. For example, to get a value from column 0 with type G_TYPE_STRING, you would write: gtk_tree_model_get (model, iter, 0, &place_string_here, -1), where place_string_here is a gchararray to be filled with the string.

    }
    g_print( "Selected (Algorithm): >> %s <<\n", ( string ? string : "NULL" ) );
    ans=g_strdup(string);

    if( string )
        g_free( string );
}

static void cb_delete( GtkButton   *button, GtkComboBox *combo )
{
    GtkTreeIter   iter;
    GtkListStore *store;

    /* Obtain currently selected item form combo box.
     * If nothing is selected, do nothing. */
    if( gtk_combo_box_get_active_iter( combo, &iter ) )
    {
        store = GTK_LIST_STORE( gtk_combo_box_get_model( combo ) );
        gtk_list_store_remove( store, &iter );
    }
}

