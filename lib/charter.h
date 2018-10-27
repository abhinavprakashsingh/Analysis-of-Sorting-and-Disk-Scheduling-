#include <cairo.h>
#include <gtk/gtk.h>
#define M_PI 3.1415926535
#define XCENTER	160.0
#define YCENTER	165.0
#define RADIUS	140.0
#define FONT_SIZE 12
#define GRAPH_WINDOW_WIDTH  680
#define GRAPH_WINDOW_HEIGHT 330

const char sortname[6][25]={"Selection Sort","Bubble Sort","Insertion Sort","Merge Sort","Quick Sort","Randomized Quick Sort"};
int dominatelist[10];
double timelist[10];
int curr_no_of_test=1232;
int LIST_SIZE[3]={6,2,6};
int type_no=0;

double color_scheme[15][3]={{0.4,1.0,0.0},{0.282353, 0.239216, 0.545098},{0.862745, 0.0784314, 0.235294},{0.729412, 0.333333, 0.827451},{0.235294, 0.701961, 0.443137},{1, 0.647059, 0},{1, 0.843137, 0},{0.815686, 0.12549, 0.564706},{0.180392, 0.545098, 0.341176},{0.0980392, 0.0980392, 0.439216},{556863, 0.556863, 0.219608},{0.466667, 0.533333, 0.6},{1, 0.498039, 0.313725},{0, 0.392157, 0},{0.498039,1,0.831373}};

static void draw_arcs(cairo_t *cr,double angle1, double angle2, short color);
static void do_drawing(cairo_t *cr);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);

void chartor(int typenum)
{
	GtkWidget *window;
	GtkWidget *darea;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), darea);

	type_no=typenum;
	g_signal_connect(G_OBJECT(darea), "draw", 
			G_CALLBACK(on_draw_event), &type_no); 
	g_signal_connect(window, "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	gtk_window_set_default_size(GTK_WINDOW(window), GRAPH_WINDOW_WIDTH, GRAPH_WINDOW_HEIGHT); 
	gtk_window_set_title(GTK_WINDOW(window), "Performance Analysis");

	gtk_widget_show_all(window);
}


static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{      
	do_drawing(cr);
	return FALSE;
}

static void do_drawing(cairo_t *cr)
{
	double prev=0.0;
	int i;
	char (*curr_list)[25]=NULL;
	switch(type_no)
	{
		case 0: curr_list=&sortname[0];
		break;
		//case 1: curr_list=&diskname[0];
	//	break;
		default:curr_list=&sortname[0];
		break;
	}

	for(i=0; i<LIST_SIZE[type_no]; i++)
	{	
		double percent=((double)dominatelist[i]*360)/curr_no_of_test;
		double angle2= percent*(M_PI/180.0);
		double texty=((double)(GRAPH_WINDOW_HEIGHT-80)/(LIST_SIZE[type_no]-1));
		char percentage[14],time[20];
		sprintf(percentage, "%8.6f%%", ((double)dominatelist[i]*100)/curr_no_of_test);
		sprintf(time, "%8.6f", timelist[i]);

		draw_arcs(cr, prev, prev+angle2, i);
		prev+=angle2;

		cairo_new_sub_path(cr);
		cairo_arc(cr, XCENTER+RADIUS+40,60+texty*i, 9, 0, 2*M_PI);
		cairo_fill(cr);

		cairo_set_source_rgb (cr, 0, 0, 0);
		if(0==i)
		{
			cairo_set_font_size(cr,FONT_SIZE+5);
			cairo_move_to(cr,XCENTER+RADIUS+30,40);
			cairo_show_text(cr,"Best Performance Percentages");
			cairo_set_font_size(cr,FONT_SIZE);
		}
		cairo_move_to(cr,XCENTER+RADIUS+60,60+texty*i);
		cairo_show_text (cr, *(curr_list+i));
		//cairo_show_text (cr, sortname[i]);
		cairo_move_to(cr,XCENTER+RADIUS+60,60+FONT_SIZE+texty*i);
		cairo_show_text (cr,percentage);
		cairo_show_text (cr, "   Total Execution Time: ");
		cairo_show_text (cr, time);
		cairo_show_text (cr, " ms");
	}

	cairo_set_source_rgba (cr, 0, 0, 0, 0.5);
	cairo_set_line_width (cr, 1.0);
	cairo_new_sub_path(cr);
	cairo_arc (cr, XCENTER, YCENTER, RADIUS+0.5, 0, 2*M_PI);
	cairo_stroke(cr);	
}

static void draw_arcs(cairo_t *cr,double angle1, double angle2, short color)
{
	cairo_set_line_width (cr, 0.001);
	cairo_set_source_rgba (cr, color_scheme[color][0], color_scheme[color][1], color_scheme[color][2], 0.6);
	cairo_new_sub_path(cr);

	cairo_arc (cr, XCENTER, YCENTER, RADIUS, angle1, angle1);
	cairo_line_to (cr, XCENTER, YCENTER);
	cairo_arc (cr, XCENTER, YCENTER, RADIUS, angle1, angle2);
	cairo_line_to (cr, XCENTER, YCENTER);
	cairo_close_path(cr);
	cairo_stroke_preserve (cr);
	cairo_fill(cr);
	cairo_stroke (cr);
}

